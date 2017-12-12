//
//  priorityQueue.cpp
//  os2
//
//  Created by Hamed Kalantari on 9/21/1396 AP.
//  Copyright © 1396 AP Hamed Kalantari. All rights reserved.
//

#include "priorityQueue.hpp"

using namespace std;


PriorityQueue::PriorityQueue() {
    
}

void PriorityQueue::enqueue(threadElement item) {
    queue.push_back(item);
    threadElement temp;
    
    for (int i=size()-1; i> 0; i--) {
        if (queue[i].priority > queue[i-1].priority) {
            temp = queue[i];
            queue[i] = queue[i-1];
            queue[i-1] = temp;
        }
        else{
            return;
        }
    }
}

threadElement PriorityQueue::dequeue() {
    if (empty()) {
        threadElement empty;
        empty.priority = -1;
        empty.thread = 'a';// it should change to nullptr
        return empty;
    }
    threadElement result = queue[0];
    queue.erase(queue.begin());
    
    return result;
}

bool PriorityQueue::empty() {
    return queue.size() == 0;
}

int PriorityQueue::size() {
    return (int) queue.size();
}

void PriorityQueue::print() {
    for (int i=0; i<size(); i++) {
        cout<<"("<<queue[i].priority<<" "<< queue[i].thread<<")"<<", ";
    }
}
