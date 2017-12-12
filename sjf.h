//sjf.h
//Impelement SJF algorithm
//Created by Mehraveh Ahmadi on 20/9/1396.

#include <scheduler.h>
#include "list.h"
#include "thread.h"


class SJFscheduler : public Scheduler
{
public:
	SJFscheduler();
	~SJFscheduler();
	ReadyToRun (Thread *thread);
	sort();
	UpdateJobTime();

private:
	List * readyList;
	 int lastTime;
    int jobTimes[4];
    int jobTimesTmp[4];
    int i;
}