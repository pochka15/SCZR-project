#include <iostream>
#include "consumer.h"
#include "utilities.h"
#include <mqueue.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>

std::string textFromMessageQueue() {
    const int kBufferSize = 64;
    char buffer[kBufferSize];
    mqd_t descriptor = mq_open("/test_queue", O_RDONLY);
    if (descriptor == -1) {
        exitWithError("Consumer can't open the queue");
    }
    unsigned long received_bytes_n = mq_receive(descriptor, buffer, kBufferSize, nullptr);
    if (received_bytes_n == -1) {
        exitWithError("Consumer can't receive the data");
    }
    return std::string(buffer, received_bytes_n);
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

//    - Open shared memory
//    - Map the object into the caller's address space
//    - Return a string from the mapped memory
