#ifndef SCZR_PROJECT_SHAREDMEMORY_H
#define SCZR_PROJECT_SHAREDMEMORY_H

#include <iostream>

const int kSharedMemoryBufferSize = 4096;

void sendViaSharedMemory(const std::string &message);

std::string textFromSharedMemory();

#endif //SCZR_PROJECT_SHAREDMEMORY_H
