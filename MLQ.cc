//MLQ.cc
//Impelement multilevel queue algorithm
//Level 1 : sjf  Scheduling
//Level 2 : priority Scheduling
// All the processes in second level queue will complete their execution according to priority scheduling.
// Queue 2 will be processed after Queue 1 becomes empty.
// Priority of Queue 2 has lower priority than in Queue 1.
//
//
/**/
//Created by Maryam Sadat Hashemi and Mahsa Razavi on 20/9/1396.
#include <MLQ.h>
#include "system.h"
#include <iostream>

MLQ::MLQ()
{
	q1 = new List;
	pq = new priorityScheduler;
	QT[0]=20;
	QT[1]=30;

    lastTime = time(0); 
}
 
MLQ::~MLQ()
{
	delete q1;
	
}


int
MLQ::ExecutionTime(Thread * thread)
{
    
    
    int currentTime = time(0);
    execution[atoi(thread->getName())] += currentTime - lastTime; 
    lastTime = time(0);
    return execution[atoi(thread->getName())] ;
    
}

void
MLQ::ReadyToRun (Thread *thread)
{
	
	DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());
	//At first, All the thread put in Queue 1
    thread->setStatus(READY);
    q1->Append(thread);
    this->setList(thread,0);
}

 
MLQ::getList(Thread * thread)
{
	return listNum[atoi(thread->getName())];
}

void
MLQ::setList(Thread * thread, int num)
{
	listNum[atoi(thread->getName())] = num;
}

Thread *
MLQ::FindNextToRun ()
{

	//check whether the q1 is empty or not 
    //  if it is not empty, use the SJF algorithm in q1
    //  else it is empty, use the priority algorithm in q2

    Thread * next_to_run;
    if(q1->IsEmpty() == false)
    {
			//If the Execution Time of thread is more than Quantum Time of Queue1, it will be 
			//removed from Queue1 and appended to Queue2.
			
	    	if(this->ExecutionTime(currentThread) >= QT[0] && this->getList(currentThread) == 0)
			{
				next_to_run = (Thread*) q1->Remove();
				pq->ReadyToRun(currentThread);
				this->setList(currentThread ,1);
			}
			else
			{
      		    next_to_run =(Thread*) q1->Remove();
			}
    }
        
    else 
    {
		//If the Execution Time of thread is more than Quantum Time of Queue2, it will be 
		//removed from Queue2 and put at the end of the Queue2.
		
    	if(this->ExecutionTime(currentThread) >= QT[1] && this->getList(currentThread) == 1)
		{
			next_to_run = pq->FindNextToRun();
			pq->ReadyToRun(currentThread);
		}
		else
		{
        	next_to_run = pq->FindNextToRun();
		}
    }
        
    return next_to_run;


}




