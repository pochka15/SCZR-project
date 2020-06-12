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

TEST(Sych, NOTIFICATION_WORKS) {
    int pid = fork();
    if (-1 == pid) {
        FAIL() << "fork error";
    }
    if (0 == pid) { // child (producer)
        sleep(2);
        notifyConsumer();
        sleep(1);
        notifyConsumer();
        exit(0);
    } else { // parent (consumer)
        waitForNewData();
        waitForNewData();
        wait(nullptr);
    }
}

void loadFunction() {
    sleep(1);
    int j = 0;
    for (int i = 0; i < 10; ++i) {
        std::cout << "Running " << i << '\n';
        j++;
    }
}

void createChildProcess(void (*functionToRun)()) {
    int pid = fork();
    if (-1 == pid) {
        FAIL() << "fork error";
    }
    if (0 == pid) { // child (producer)
        functionToRun();
        exit(0);
    }
}

//TODO(@pochka15):
TEST(MainTests, test_6) {
    int processes_number = 4;
//    It doesn't work as written. All the child processes run one by one
    for (int i = 0; i < processes_number; ++i) {
        createChildProcess(loadFunction);
    }
    while(wait(nullptr) > 0); // wait for child processes
//    Measure time

}