#ifndef BINARY_TREE_QUEUE_H_
#define BINARY_TREE_QUEUE_H_

#include "node.h"

typedef struct Queue {
    Node *front;
    Node *back;
    int sz;
} Queue;

void QueueInit(Queue *q);
void QueuePush(Queue *q, void* val);
void* QueuePeek(Queue *q);
void* QueuePop(Queue *q);

#endif
