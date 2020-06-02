#ifndef SCZR_PROJECT_SHAREDMEMORY_H
#define SCZR_PROJECT_SHAREDMEMORY_H

#include <iostream>

void sendViaSharedMemory(const std::string &message);

std::string textFromSharedMemory();

#endif //SCZR_PROJECT_SHAREDMEMORY_H
