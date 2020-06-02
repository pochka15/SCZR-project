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
    int fd = shm_open("/shmpath", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
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
    sleep(10); // Wait until consumer starts using the message queue
    /* Unlink the shared memory object. Even if the peer process
   is still using the object, this is okay. The object will
   be removed only after all open references are closed. */
    shm_unlink("/shmpath");
}

std::string textFromSharedMemory() {
    const int kBufferSize = 64;
//    Open shared memory
    int fd = shm_open("/shmpath", O_RDWR, 0);
    if (fd == -1)
        exitWithError("Consumer can't open the shared memory");
//    Map the data into the caller's address space
    void *mapped_memory = mmap(NULL, kBufferSize,
                               PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_memory == MAP_FAILED)
        exitWithError("Consumer can't map the memory");
    return std::__cxx11::string((char *) mapped_memory);
}

