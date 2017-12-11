//MLQ.h
//Impelement multilevel queue algorithm
//Level 1 : priority  Scheduling
//Level 2 : sjf Scheduling
// All the processes in second level queue will complete their execution according to SJF scheduling.
// Queue 2 will be processed after Queue 1 becomes empty.
// Priority of Queue 2 has lower priority than in Queue 1.
//
//
//Created by Maryam Sadat Hashemi on 20/9/1396.
#include <scheduler.h>
#include "list.h"
#include "thread.h"

class MLQ : public Scheduler
{
public:
	MLQ();
	~MLQ();

private:
	List * multilevellist;
	//Quantum Time of each queue
	int QT[2];
}
