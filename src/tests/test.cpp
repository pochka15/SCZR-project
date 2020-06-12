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

TEST(ShMem, CHILD_PARENT_PROCESSES_CORRECTED_TEXT_RECEIVED) {
    std::string text = std::string(4095, 'a');
    int pid = fork();
    if (-1 == pid) {
        FAIL() << "fork error";
    }
    if (0 == pid) { // child
        sendViaSharedMemory(text);
        exit(0);
    } else { // parent
        sleep(1);
        ASSERT_EQ(text, textFromSharedMemory());
    }
}