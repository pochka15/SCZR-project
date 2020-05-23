#ifndef SCZR_PROJECT_CONSUMER_H
#define SCZR_PROJECT_CONSUMER_H

/**
 * Receive a text from the message queue
 */
std::string textFromMessageQueue();

/**
 * Receive a text from the shared memory
 * @return
 */
std::string textFromSharedMemory();

#endif //SCZR_PROJECT_CONSUMER_H
