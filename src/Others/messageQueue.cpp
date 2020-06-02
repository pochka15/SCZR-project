#include "messageQueue.h"
#include <mqueue.h>
#include "utilities.h"
#include <unistd.h>

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

std::string textFromMessageQueue() {
    const int kBufferSize = 64;
    char buffer[kBufferSize];
    mqd_t descriptor = mq_open("/test_queue", O_RDONLY);
    if (descriptor == -1) {
        exitWithError("Consumer can't open the queue");
    }
    ssize_t received_bytes_n = mq_receive(descriptor, buffer, kBufferSize, nullptr);
    if (received_bytes_n == -1) {
        exitWithError("Consumer can't receive the data");
    }
    return std::string(buffer, received_bytes_n);
}
