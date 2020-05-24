#include <iostream>
#include "producer.h"

int main(int argc, char *argv[]) {
    sendViaSharedMemory("Hello world");
//    sendViaMessageQueue("Hello world");
    return 0;
}