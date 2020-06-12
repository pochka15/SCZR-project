#include "gtest/gtest.h"
#include "producer.h"
#include "consumer.h"
#include "database.h"

TEST(ShMem, singleThreadCorrectBytesReceived) {
    std::string text = std::string(4095, 'a');
    // sendViaSharedMemory(text);
//    getData();
//    ASSERT_TRUE(text == textFromSharedMemory());
}

TEST(ShMem, resultsAreCreated) {
    create_results();
}

TEST(ShMem, kasia) {
    std::string text = generatestring();
    sendViaSharedMemory(text);
    std::cout << text;
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
        int j = 0;
        for (int i = 0; i < 10; ++i) {
            std::cout << "Running " << i << '\n';
            j++;
        }
        exit(0);
    }
}

TEST(MainTests, test_6) {
    int processes_number = 4;
    //TODO(@pochka15):
    //    It doesn't work as written. All the child processes run one by one
    for (int i = 0; i < processes_number; ++i) {
        int pid = fork();
        if (-1 == pid) {
            FAIL() << "fork error";
        }
        if (0 == pid) { // child (producer)
            waitForNewData();
            for (int j = 0; j < 10; ++j) {
                std::cout << getpid() << '\n';
            }
            exit(0);
        }
    }
    for (int i = 0; i < processes_number; ++i) {
        notifyConsumer(); // It's a hotfix, Producer and consumer synchronization is used here
    }
    while (wait(nullptr) > 0); // wait for child processes
//    TODO(@pochka15): Measure time
}

