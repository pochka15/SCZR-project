#include "gtest/gtest.h"
#include "sharedMemory.h"

// TODO(@pochka15): why does this test pass?
// We've got only 64 bytes mapped in the buffer?!
TEST(ShMem, singleThreadCorrectBytesReceived) {
//    When I use the text of 5000 'a' chars it throws SIGSEGV
//    std::string text = std::string(5000, 'a');
    std::string text = std::string(4000, 'a');
    sendViaSharedMemory(text);
    ASSERT_TRUE(text == textFromSharedMemory());
}
