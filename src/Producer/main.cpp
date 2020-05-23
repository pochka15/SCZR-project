#include <iostream>
#include "producer.h"

int main() {
    sendViaSharedMemory("Hello world");
    return 0;
}