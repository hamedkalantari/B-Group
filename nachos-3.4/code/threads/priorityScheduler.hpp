

#ifndef priorityScheduler_hpp
#define priorityScheduler_hpp


#include "scheduler.h"
#include "priorityQueue.hpp"


class PriorityScheduler : public Scheduler {
    PriorityQueue* queue;
    
public:
    
    PriorityScheduler();
    ~PriorityScheduler();
    
    void ReadyToRun(Thread* t);
    Thread* FindNextToRun();
};

#endif /* priorityScheduler_hpp */
