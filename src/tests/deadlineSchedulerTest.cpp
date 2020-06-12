#include "deadlineScheduling.h"
#include "gtest/gtest.h"
#include "producer.h"
#include "consumer.h"
#include "database.h"
#include "utilities.h"

void *runDeadline(void *args) {
    sched_attr attr;
    unsigned int flags = 0;

    attr.size = sizeof(attr);
    attr.sched_flags = 0;
    attr.sched_nice = 0;
    attr.sched_priority = 0;

    /* creates a 10ms/11ms reservation */
    attr.sched_policy = SCHED_DEADLINE;
    attr.sched_runtime = 10 * 1000 * 1000;
    attr.sched_deadline = 11 * 1000 * 1000;
    attr.sched_period = 11 * 1000 * 1000;

    int ret = sched_setattr(0, &attr, flags);
    if (ret < 0) {
        exitWithError("sched_setattr");
    }
    for (int i = 0; i < 100; ++i) {
        std::cout << "+++++++++++++++++++++++\n";
    }
    exit(0);
}

//    Need to run with sudo
TEST(Sched, DEADLINE_SCHEDULING_THREADS_WORKS) {
//    run producer process and set the scheduling policy
//    set the scheduling policy of a test
//    observe the result
    std::cout << "You need to run this test as SUDO!";
    pthread_t thread;
    pthread_create(&thread, NULL, runDeadline, NULL);

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
        FAIL();
    }
    for (int i = 0; i < 100; ++i) {
        std::cout << "----\n";
    }
    pthread_join(thread, NULL);
}

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
    for (int i = 0; i < 100; ++i) {
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
        FAIL();
    }
    for (int i = 0; i < 100; ++i) {
        std::cout << "----\n";
    }
}


TEST(Sched, DEADLINE_SCHEDULING_PROCESSES_WORKS) {
//    run producer process and set the scheduling policy
//    set the scheduling policy of a test
//    observe the result
    std::cout << "You need to run this test as SUDO!";
    int pid = fork();
    if (-1 == pid) {
        FAIL() << "fork error";
    }
    if (0 == pid) { // child (producer)
        runProducer();
        exit(0);
    } else { // parent (consumer)
        runConsumer();
        wait(nullptr);
    }
}
