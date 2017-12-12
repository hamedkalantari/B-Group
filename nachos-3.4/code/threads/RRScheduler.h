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

    void Print();

private:
    List *readyList; //queue of threads that are ready to run,
        //but not running
};

#endif //CODE_RRSCHEDULER_H
