#include <iostream>
#include "producer.h"

int main() {
    sendViaMessageQueue("Hello world");
    std::cout << "Message was sent\n";
    return 0;
}