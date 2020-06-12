#include <iostream>
#include "consumer.h"
#include "schedulingPolicies.h"

int main() {
    std::cout << "Text from shared memory: " << textFromSharedMemory();
    return 0;
}