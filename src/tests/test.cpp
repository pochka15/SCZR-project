#include "gtest/gtest.h"
#include "sharedMemory.h"

TEST(ShMem, textComesFromShMem) {
    FAIL();
    // The test will not work, because there must be run 2 processes: Consumer-app and Producer-app
    sendViaSharedMemory("Hello wold");
    ASSERT_EQ(textFromSharedMemory(), "Hello world");
}
