#include <database.h>
#include <iostream>
#include <wait.h>
#include "producer.h"
#include "deadlineScheduling.h"
#include "utilities.h"
#include <pthread.h>
#include <schedulingPolicies.h>


void runProducer() {
    std::cout << "Producer function\n";
    sched_attr attr;
    unsigned int flags = 0;

    attr.size = sizeof(attr);
    attr.sched_flags = 0;
    attr.sched_nice = 0;
    attr.sched_priority = 0;

    /* creates a 10ms/10ms reservation */
    attr.sched_policy = SCHED_DEADLINE;
    attr.sched_runtime = 10 * 1000 * 1000;
    attr.sched_deadline = 10 * 1000 * 1000;
    attr.sched_period = 10 * 1000 * 1000;

    int ret = sched_setattr(0, &attr, flags);
    if (ret < 0) {
        exitWithError("sched_setattr");
    }
    sleep(10);
    for (int i = 0; i < 10000000; ++i) {
        std::cout << "+++++++++++++++++++++++\n";
    }
}

void runConsumer() {
    std::cout << "Consumer function\n";
    sched_attr attr;
    unsigned int flags = 0;

    attr.size = sizeof(attr);
    attr.sched_flags = 0;
    attr.sched_nice = 0;
    attr.sched_priority = 0;

    /* creates a 10ms/60ms reservation */
    attr.sched_policy = SCHED_DEADLINE;
    attr.sched_runtime = 10 * 1000 * 1000;
    attr.sched_deadline = 60 * 1000 * 1000;
    attr.sched_period = 60 * 1000 * 1000;

    int ret = sched_setattr(0, &attr, flags);
    if (ret < 0) {
        exitWithError("sched error");
    }
    sleep(10);
    for (int i = 0; i < 10000000; ++i) {
        std::cout << "----\n";
    }
}

void *runDeadline(void *args) {
    std::cout << sched_getcpu() << '\n';
//    sched_attr attr;
//    unsigned int flags = 0;
//
//    attr.size = sizeof(attr);
//    attr.sched_flags = 0;
//    attr.sched_nice = 0;
//    attr.sched_priority = 0;
//
//    /* creates a 10ms/10ms reservation */
//    attr.sched_policy = SCHED_DEADLINE;
//    attr.sched_runtime = 10 * 1000 * 1000;
//    attr.sched_deadline = 10 * 1000 * 1000;
//    attr.sched_period = 10 * 1000 * 1000;
//
//    int ret = sched_setattr(0, &attr, flags);
//    if (ret < 0) {
//        exitWithError("sched_setattr");
//    }
//    sleep(4);
//    for (int i = 0; i < 100; ++i) {
//        for (int j = 0; j < 10; ++j) {
////            std::cout << i << ' ';
//        }
////        std::cout << '\n';
//    }
    exit(0);
}

void threadsSchedulingTest() {
    std::cout << "Parent:" << sched_getcpu() << '\n';
//    cpu_set_t cpuset;
//    CPU_ZERO(&cpuset);
//    CPU_SET(1, &cpuset);
//    int s = sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);
//    if (s != 0)
//        exitWithError("affinity error");
//    std::cout << "After: " << sched_getcpu() << '\n';

    //    std::cout << "You need to run this test as SUDO!";
    pthread_t thread;
    pthread_create(&thread, NULL, runDeadline, NULL);
//
//    sched_attr attr;
//    unsigned int flags = 0;
//
//    attr.size = sizeof(attr);
//    attr.sched_flags = 0;
//    attr.sched_nice = 0;
//    attr.sched_priority = 0;
//
//    /* creates a 10ms/60ms reservation */
//    attr.sched_policy = SCHED_DEADLINE;
//    attr.sched_runtime = 10 * 1000 * 1000;
//    attr.sched_deadline = 60 * 1000 * 1000;
//    attr.sched_period = 60 * 1000 * 1000;
//
//    int ret = sched_setattr(0, &attr, flags);
//    if (ret < 0) {
//        exitWithError("set_attrib");
//    }
//    sleep(4);
//    for (int i = 0; i < 100; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            std::cout << i << ' ';
//        }
//        std::cout << '\n';
//    }
    pthread_join(thread, NULL);
}

void processesSchedulingTest() {
    std::cout << "You need to run this test as SUDO!";
    int pid = fork();
    if (-1 == pid) {
        exitWithError("fork error");
    }
    if (0 == pid) { // child (producer)
        runProducer();
        exit(0);
    } else { // parent (consumer)
        runConsumer();
        wait(nullptr);
    }
}

int main(int argc, char *argv[]) {
//    sendViaSharedMemory("Hello world");
//    generateRandomlyFilledTable();
    enableFifoPolicy(2);
    for (int i = 0; i < 1000000; ++i) {
        std::cout << "producer\n";
    }
    return 0;
}