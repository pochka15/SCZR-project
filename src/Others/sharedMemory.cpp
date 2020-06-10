#include <string>
#include <sys/mman.h>
#include <cstring>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include "sharedMemory.h"
#include "utilities.h"

void sendViaSharedMemory(const std::string &message) {
    const int kBufferSize = 64;
//    Open shared memory
    int fd = shm_open("/sh_mem", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1)
        exitWithError("cannot open shared memory");
//    Allocate the memory
    if (ftruncate(fd, kBufferSize) == -1)
        exitWithError("cannot call ftruncate");
//    Map the object into the caller's address space
    void *mapped_memory = mmap(NULL, kBufferSize,
                               PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_memory == MAP_FAILED)
        exitWithError("mmap error");
//    Copy data to the shared memory
    memcpy(mapped_memory, message.c_str(), message.length() + 1 /* 1 is for null terminate */);
}

std::string textFromSharedMemory() {
    const int kBufferSize = 64;
//    Open shared memory
    int fd = shm_open("/sh_mem", O_RDWR, 0);
    if (fd == -1)
        exitWithError("Consumer can't open the shared memory");
//    Map the data into the caller's address space
    void *mapped_memory = mmap(NULL, kBufferSize,
                               PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_memory == MAP_FAILED)
        exitWithError("Consumer can't map the memory");
    shm_unlink("/sh_mem");
    return std::__cxx11::string((char *) mapped_memory);
}

