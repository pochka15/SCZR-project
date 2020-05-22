#include <mqueue.h>
#include <string>
#include "producer.h"
#include "utilities.h"

void sendViaMessageQueue(const std::string &message) {
    mqd_t descriptor = mq_open("/test_queue", O_RDWR);
    if (descriptor == -1) {
        exitWithError("Cannot open the queue\n");
    }
    ssize_t sent_bytes = mq_send(descriptor, message.data(), message.length(), 0);
    if (sent_bytes == -1) {
        exitWithError("Cannot receive the data");
    }
}

