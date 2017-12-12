//
// Created by Ehsan Aliakbar on 12/11/17.
//

#include "RRScheduler.h"

RRScheduler::RRScheduler() {
    readyList = new List;
}

RRScheduler::~RRScheduler() {
    delete readyList;
}

void RRScheduler::ReadyToRun(Thread *thread) {
    DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());

    thread->setStatus(READY);
    readyList->Append((void *)thread);
}

Thread* RRScheduler::FindNextToRun() {
    return (Thread *)readyList->Remove();
}

void
RRScheduler::Print()
{
    printf("Ready list contents:\n");
    readyList->Mapcar((VoidFunctionPtr) ThreadPrint);
}