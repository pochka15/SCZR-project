#include <iostream>
#include "consumer.h"
#include "utilities.h"
#include <mqueue.h>


std::string messageQueueText() {
    char buffer[1024];

//    TODO(@pochka15): I don't know. If I open the queue with the same name as in consumer's code then will it be the same queue or just another?
    mqd_t descriptor = mq_open("/test_queue", O_RDONLY);
    if (descriptor == -1) {
        exitWithError("Cannot open the queue\n");
    }
    unsigned long received_bytes = mq_receive(descriptor, buffer, 1024, nullptr);
    if (received_bytes == -1) {
        exitWithError("Cannot receive the data");
    }

    return std::string(buffer, received_bytes);
}

