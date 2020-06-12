//
// Created by pochka15 on 6/12/20.
//

#include <sched.h>
#include "schedulingPolicies.h"
#include "utilities.h"

void enableFifoPolicy(int priority) {
    sched_param param;
    param.sched_priority = priority;
    int rc = sched_setscheduler(0, SCHED_FIFO, &param);
    if (-1 == rc) {
        exitWithError("Cannot set the FIFO scheduler\n");
    }
}
