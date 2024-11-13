#ifndef BINARY_TREE_QUEUE_H_
#define BINARY_TREE_QUEUE_H_

#include "node.h"

typedef struct Queue {
    Node *front;
    Node *back;
    int sz;
} Queue;

void QueueInit(Queue *q);
void QueuePush(Queue *q, int val);
int QueuePeek(Queue *q);
int QueuePop(Queue *q);

#endif
