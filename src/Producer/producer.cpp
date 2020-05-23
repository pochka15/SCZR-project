#include <mqueue.h>
#include <string>
#include "producer.h"
#include "utilities.h"
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>


void sendViaMessageQueue(const std::string &message) {
//    TODO(@pochka15): tihnk about how to message queue will be closed? By whom? When?
    mqd_t descriptor = mq_open("/test_queue", O_RDWR);
    if (descriptor == -1) {
        exitWithError("Cannot open the queue\n");
    }
    ssize_t sent_bytes = mq_send(descriptor, message.data(), message.length(), 0);
    if (sent_bytes == -1) {
        exitWithError("Cannot receive the data");
    }
}

void sendViaSharedMemory(const std::string &message) {
    const int kBufferSize = 64;
//    Open shared memory
    int fd = shm_open("/shmpath", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1)
        exitWithError("cannot open shared memory");
//    Truncate the memory
    if (ftruncate(fd, kBufferSize) == -1)
        exitWithError("cannot call ftruncate");
//    Map the object into the caller's address space
    void *mapped_memory = mmap(NULL, kBufferSize,
            PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_memory == MAP_FAILED)
        exitWithError("mmap error");
//    Copy data to the shared memory
    memcpy(mapped_memory, message.c_str(), kBufferSize);
    sleep(10);
    /* Unlink the shared memory object. Even if the peer process
   is still using the object, this is okay. The object will
   be removed only after all open references are closed. */
    shm_unlink("/shmpath");
}

