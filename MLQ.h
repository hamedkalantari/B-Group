//MLQ.h
//Impelement multilevel queue algorithm
//Level 1 : priority  Scheduling
//Level 2 : sjf Scheduling
// All the processes in second level queue will complete their execution according to SJF scheduling.
// Queue 2 will be processed after Queue 1 becomes empty.
// Priority of Queue 2 has lower priority than in Queue 1.
//
//
//Created by Maryam Sadat Hashemi and Mahsa Razavi on 20/9/1396.

#ifndef MLQ_H
#define MLQ_H
#include "scheduler.h"
#include "list.h"
#include "thread.h"
#include "priorityScheduler.h"
#include <time.h> 
#include "sjf.h"

class MLQ : public Scheduler
{
public:
	MLQ();
	~MLQ();

	int lastTime;

	int listNum[10];

	int execution[10];

	void setList(Thread * thread, int num); // Sets list number

	int getList(Thread * thread); //Returns list number

	int ExecutionTime(Thread * thread); // Calculate job times

	void ReadyToRun(Thread* thread);// Thread can be dispatched.

	Thread* FindNextToRun();



	SJFscheduler sq;
	priorityScheduler pq;

	//Quantum Time of each queue
	int QT[2];
};
#endif
