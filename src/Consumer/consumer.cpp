#include <iostream>
#include "consumer.h"
#include "sharedMemory.h"
#include "messageQueue.h"
#include "database.h"

void runConsumer() {
//    std::cout << textFromSharedMemory() << std::endl;
    generateRandomDatabaseFile();
}