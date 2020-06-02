#include "sharedMemory.h"
#include "messageQueue.h"

void runProducer() {
    sendViaSharedMemory("Hello world");
}
