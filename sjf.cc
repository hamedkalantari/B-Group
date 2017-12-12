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



