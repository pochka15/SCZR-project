#include <iostream>

#include "consumer.h"

int main() {
//    std::cout << textFromMessageQueue();
    std::cout << textFromSharedMemory() << '\n';
    return 0;
}