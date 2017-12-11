//MLQ.cc
//Impelement multilevel queue algorithm
//Level 1 : sjf  Scheduling
//Level 2 : priority Scheduling
// All the processes in second level queue will complete their execution according to priority scheduling.
// Queue 2 will be processed after Queue 1 becomes empty.
// Priority of Queue 2 has lower priority than in Queue 1.
//
//
//Created by Maryam Sadat Hashemi on 20/9/1396.
#include <MLQ.h>
#include "system.h"

MLQ::MLQ()
{
	multiLevelList = new List<Thread *>[2];
	QT[0]=20;
	QT[1]=30;
}
 
MLQ::~MLQ
{
	delete multiLevelList;
}

void
MLQ::ReadyToRun (Thread *thread)
{
	DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());
	//At first, All the thread put in Queue 1
    thread->setStatus(READY);
    multiLevelList[0].Append(thread);
}

Thread *
MLQ::FindNextToRun ()
{
	//check whether the multilevellist[0] is empty or not 
    //  if it is not empty, use the priority algorithm in multilevellist[0]
    //  else it is empty, use the SJF algorithm in multilevellist[1]

    Thread * next_to_run;
    if(multiLevelList[0].IsEmpty() == false)
    {
			//If the Execution Time of thread is more than Quantum Time of Queue1, it will be 
			//removed from Queue1 and appended to Queue2.
			//assume that we have execution time in thread as an attribute so it  maybe will change 
			//in other commits. and also assume that we have function "getlist" that is shown each thread 
			//ralated to which Queue.
	    	if(currentThread->executionTime >=QT[0] && currentThread->getlist() == 0)
			{
				next_to_run = multiLevelList[0].Remove();
				multiLevelList[1].Append(currentThread);
			}
			else
			{
      		    next_to_run = multiLevelList[0].Remove();
			}
    }
        
    else 
    {
		//If the Execution Time of thread is more than Quantum Time of Queue2, it will be 
		//removed from Queue2 and put at the end of the Queue2.
		//assume that we have execution time in thread as an attribute so it  maybe will change 
		//in other commits. and also assume that we have function "getlist" that is shown each thread 
		//ralated to which Queue.
    	if(currentThread->executionTime >=QT[1] && currentThread->getlist() == 1)
		{
			next_to_run = multiLevelList[1].Remove();
			multiLevelList[1].Append(currentThread);
		}
		else
		{
        	next_to_run = multiLevelList[1].Remove();
		}
    }
        
    return next_to_run;
}


