//sjf.h
//Impelement SJF algorithm
//Created by Mehraveh Ahmadi on 20/9/1396.
#include <sjf.h>
#include "system.h"

SJFscheduler::SJFscheduler()
{
	readyList = new List;
	lastTime = time(0); 
    i = 0;
}
 
SJFscheduler::~SJFscheduler
{
	delete readyList;
}


void
SJFscheduler::ReadyToRun (Thread *thread)
{
    DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());

    thread->setStatus(READY);
    readyList->Append((void *)thread);
}

Thread *
SJFscheduler::FindNextToRun ()
{  
      UpdateJobTime();
   List* temp= new List;
   int minTime = 9999999;

   printf("next to  run \n");
    if (readyList->IsEmpty()) return NULL;
    while(!readyList->IsEmpty()){
        Thread * t = (Thread* ) readyList->Remove();
        if(jobTimes[atoi(t->getName())] < minTime) 
        {
            minTime = jobTimes[atoi(t->getName())];
        } 
        temp->Append(t);
        printf("min time%d\n", minTime);
    }
    readyList = temp;
       Thread *a =  (Thread *) readyList->Remove();
     while (jobTimes[atoi(a->getName())] > minTime){
       readyList->Append((void *)a);
       a = (Thread *) readyList->Remove();

    }
    return a;
}

void 
SJFscheduler::sort()
{
 //,,,,,,,,,,,,,,,
}

void
SJFscheduler::UpdateJobTime()
{
	 char *name = currentThread->getName();
     
      if (name == "main")
    {
        lastTime = time(0);
        return ;
    }
    if(i == 3)
    {
        for( int j = 0 ; j < 4 ; j++)
            jobTimes[j] = jobTimesTmp[j];
        i = 0;
    }
    int currentTime = time(0);
    jobTimesTmp[atoi(currentThread->getName())] = currentTime - lastTime;
    std::cout << "time : " << jobTimesTmp[atoi(currentThread->getName())]<< std::endl;
    lastTime = time(0);
    i++;
}

void
Scheduler::Run (Thread *nextThread)
{
    Thread *oldThread = currentThread;
    
#ifdef USER_PROGRAM     // ignore until running user programs 
    if (currentThread->space != NULL) { // if this thread is a user program,
        currentThread->SaveUserState(); // save the user's CPU registers
  currentThread->space->SaveState();
    }
#endif
    
    oldThread->CheckOverflow();       // check if the old thread
              // had an undetected stack overflow

    currentThread = nextThread;       // switch to the next thread
    currentThread->setStatus(RUNNING);      // nextThread is now running
    
    DEBUG('t', "Switching from thread \"%s\" to thread \"%s\"\n",
    oldThread->getName(), nextThread->getName());
    
    // This is a machine-dependent assembly language routine defined 
    // in switch.s.  You may have to think
    // a bit to figure out what happens after this, both from the point
    // of view of the thread and from the perspective of the "outside world".

    SWITCH(oldThread, nextThread);
    
    DEBUG('t', "Now in thread \"%s\"\n", currentThread->getName());

    // If the old thread gave up the processor because it was finishing,
    // we need to delete its carcass.  Note we cannot delete the thread
    // before now (for example, in Thread::Finish()), because up to this
    // point, we were still running on the old thread's stack!
    if (threadToBeDestroyed != NULL) {
        delete threadToBeDestroyed;
  threadToBeDestroyed = NULL;
    }
    
#ifdef USER_PROGRAM
    if (currentThread->space != NULL) {   // if there is an address space
        currentThread->RestoreUserState();     // to restore, do it.
  currentThread->space->RestoreState();
    }
#endif
}
void Print(){
  
}

