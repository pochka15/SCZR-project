#include "gtest/gtest.h"
#include "producer.h"
#include "consumer.h"
#include "database.h"

TEST(ShMem, singleThreadCorrectBytesReceived) {
    std::string text = std::string(4095, 'a');
   // sendViaSharedMemory(text);
    getData();
    ASSERT_TRUE(text == textFromSharedMemory());
}


TEST(ShMem, kasia) {
    std::string text = generatestring();
    sendViaSharedMemory(text);
    std::cout<<text;
    getData();
    ASSERT_TRUE(text == textFromSharedMemory());
}
