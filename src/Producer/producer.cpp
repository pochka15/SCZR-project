#include "database.h"
#include <sys/mman.h>
#include <fcntl.h>
#include "utilities.h"
#include "producer.h"

#include <unistd.h>
#include <cstring>
#include <mqueue.h>

void sendViaSharedMemory(const std::string &message) {
//    Open shared memory
    int fd = shm_open("/sh_mem", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1)
        exitWithError("cannot open shared memory");
//    Allocate the memory
    if (ftruncate(fd, kSharedMemoryBufferSize) == -1)
        exitWithError("cannot call ftruncate");
//    Map the object into the caller's address space
    void *mapped_memory = mmap(NULL, kSharedMemoryBufferSize,
                               PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_memory == MAP_FAILED)
        exitWithError("mmap error");
//    Copy data to the shared memory
    memcpy(mapped_memory, message.c_str(), message.length() + 1 /* 1 is for null terminate */);
}

void sendViaMessageQueue(const std::string &message) {
    struct mq_attr queue_attributes;
    queue_attributes.mq_flags = 0;
    queue_attributes.mq_maxmsg = 10;
    queue_attributes.mq_msgsize = message.length() + 1;
    queue_attributes.mq_curmsgs = 0;
    mqd_t descriptor = mq_open("/test_queue", O_CREAT | O_RDWR, 0644, &queue_attributes);
    if (descriptor == -1) {
        exitWithError("Producer cannot open message queue");
    }
    ssize_t send_result = mq_send(descriptor, message.c_str(),
                                  message.length() + 1 /* 1 is for null terminate */, 0);
    if (send_result == -1) {
        exitWithError("Producer cannot send the data");
    }
    sleep(10); // Wait until consumer starts using the message queue
    mq_unlink("/test_queue");
}

void notifyConsumer() {
    struct mq_attr queue_attributes;
    queue_attributes.mq_flags = 0;
    queue_attributes.mq_maxmsg = 10;
    queue_attributes.mq_msgsize = 1;
    queue_attributes.mq_curmsgs = 0;
    mqd_t descriptor = mq_open("/notification_queue", O_CREAT | O_RDWR, 0644, &queue_attributes);
    if (descriptor == -1) {
        exitWithError("Producer cannot open notification queue");
    }
    ssize_t send_result = mq_send(descriptor, "\0", 1, 0);
    if (send_result == -1) {
        exitWithError("Producer cannot send the data");
    }
    mq_unlink("/test_queue");
}
