

#include "priorityScheduler.hpp"
#include "priorityQueue.hpp"


PriorityScheduler::PriorityScheduler() {
    queue = new PriorityQueue;
}

PriorityScheduler::~PriorityScheduler() {
    delete queue;
}

Thread* PriorityScheduler::FindNextToRun() {
    // fetch next thread in queue
    threadElement next = pq->dequeue();
    
    // check if we don't have ant threads available
    if (next.thread == NULL)
        return NULL;
    
    return next.thread;
}

void PriorityScheduler::ReadyToRun(Thread* t) {
    threadElement item;
    item.thread = t;
    item.priority = t->getPriority();
    queue->enqueue(item);
}
