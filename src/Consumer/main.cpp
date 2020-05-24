#include <iostream>

#include "consumer.h"

int main() {
    std::cout << textFromSharedMemory() << '\n';
//    std::cout << textFromMessageQueue() << '\n';
    return 0;
}