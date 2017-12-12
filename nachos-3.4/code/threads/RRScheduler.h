//
// Created by Ehsan Aliakbar on 12/11/17.
//

#include "scheduler.h"

#ifndef CODE_RRSCHEDULER_H
#define CODE_RRSCHEDULER_H

class RRScheduler : public Scheduler {
public:
    RRScheduler();
    ~RRScheduler();

    void ReadyToRun(Thread* thread);
    Thread* FindNextToRun();
};

#endif //CODE_RRSCHEDULER_H
