

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
    node next = pq->dequeue();
    
    // check if we don't have ant threads available
    if (next.thread == nullptr)
        return nullptr;
    
    return next.thread;
}

void PriorityScheduler::ReadyToRun(Thread* t) {
    threadElement item;
    item.thread = t;
    item.priority = t->getPriority();
    queue->enqueue(item);
}
