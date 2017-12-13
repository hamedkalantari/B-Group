

#ifndef priorityQueue_hpp
#define priorityQueue_hpp


#include <iostream>
#include <stdio.h>
#include <vector>
#include "thread.h"

using namespace std;


struct threadElement {
   Thread* thread;
    int priority;
};


class PriorityQueue {
private:
    // this will contain threads with their priorities
    vector<threadElement> queue;
    
public:
    // constructor
    PriorityQueue();
    
    // Insert a new item into the priority queue
    void enqueue(threadElement item);
    
    // return front element in queue and removes it
    threadElement dequeue();
    
    // check whether priority is empty
    bool empty();
    
    // return queue's size
    int size();
    
    // print queue
    void print();
};


#endif /* priorityQueue_hpp */
