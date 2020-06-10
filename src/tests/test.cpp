#include "gtest/gtest.h"
#include "sharedMemory.h"

TEST(ShMem, singleThreadCorrectBytesReceived) {
    std::string text = std::string(4095, 'a');
    sendViaSharedMemory(text);
    ASSERT_TRUE(text == textFromSharedMemory());
}
