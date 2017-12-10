//
//  priorityQueue.hpp
//  os_proj2
//
//  Created by Hamed Kalantari on 9/19/1396 AP.
//  Copyright © 1396 AP Hamed Kalantari. All rights reserved.
//

#ifndef priorityQueue_hpp
#define priorityQueue_hpp

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
    void enqueue(node item);
    
    // return front element in queue and removes it
    threadElement dequeue();
    
    // return front element in queue
    threadElement front();
    
    // check whether priority is empty
    bool empty();
    
    // return queue's size
    int size();
    
    // print queue
    void print();
};

#endif /* priorityQueue_hpp */
