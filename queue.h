#ifndef QUEUE_H
#define QUEUE_H

#include "graphnode.h"

class Queue
{
public:
    Queue();
    GraphNode* head;
    GraphNode* tail;
    void enqueue(char ID, int distance);
    GraphNode* dequeue();
    bool is_empty();

};

#endif // QUEUE_H
