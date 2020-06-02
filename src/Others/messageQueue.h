#ifndef SCZR_PROJECT_MESSAGEQUEUE_H
#define SCZR_PROJECT_MESSAGEQUEUE_H

#include <string>

/**
 * Receive a text from the message queue
 */
std::string textFromMessageQueue();


void sendViaMessageQueue(const std::string &message);


#endif //SCZR_PROJECT_MESSAGEQUEUE_H
