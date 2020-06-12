#include "deadlineScheduling.h"
#include "gtest/gtest.h"
#include "producer.h"
#include "consumer.h"
#include "database.h"
#include "utilities.h"

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
    if (0 == pid) { // child (producer)
        sendViaSharedMemory(text);
        exit(0);
    } else { // parent (consumer)
        sleep(1);
        ASSERT_EQ(text, textFromSharedMemory());
    }
}

TEST(MessageQueue, CHILD_PARENT_PROCESSES_CORRECTED_TEXT_RECEIVED) {
    std::string text = "Hello world";
    int pid = fork();
    if (-1 == pid) {
        FAIL() << "fork error";
    }
    if (0 == pid) { // child (producer)
        sendViaMessageQueue(text);
        exit(0);
    } else { // parent (consumer)
        sleep(1);
        ASSERT_EQ(text, textFromMessageQueue());
    }
}