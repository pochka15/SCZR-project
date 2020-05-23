#include <iostream>
#include "consumer.h"
#include "utilities.h"
#include <mqueue.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>

//TODO(@pochka15): uncomment
//std::string textFromMessageQueue() {
//    char buffer[1024];
//
////    TODO(@pochka15): I don't know. If I open the queue with the same name as in producers's code then will it be the same queue or just another one?
//    mqd_t descriptor = mq_open("/test_queue", O_RDONLY);
//    if (descriptor == -1) {
//        exitWithError("Cannot open the queue\n");
//    }
//    unsigned long received_bytes = mq_receive(descriptor, buffer, 1024, nullptr);
//    if (received_bytes == -1) {
//        exitWithError("Cannot receive the data");
//    }
//
//    return std::string(buffer, received_bytes);
//}

std::string textFromSharedMemory() {
    const int kBufferSize = 64;
//    Open shared memory
    int fd = shm_open("/shmpath", O_RDONLY, 0);
    if (fd == -1)
        exitWithError("shm_open");
//    Map the object into the caller's address space
    void *mapped_memory = mmap(NULL, kBufferSize,
                               PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_memory == MAP_FAILED)
        exitWithError("mmap error");
//    Return the text from shared memory
    return std::__cxx11::string((char *) mapped_memory);
}

