#include <iostream>
#include "consumer.h"
#include "schedulingPolicies.h"

int main() {
//    std::cout << textFromSharedMemory();
    enableFifoPolicy(1);
    for (int i = 0; i < 1000000; ++i) {
        std::cout << "consumer\n";
    }
    return 0;
}