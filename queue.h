#ifndef BINARY_TREE_QUEUE_H_
#define BINARY_TREE_QUEUE_H_

#include "node.h"

typedef struct VoidQueue {
    VoidNode *front;
    VoidNode *back;
    int sz;
} VoidQueue;

void VoidQueueInit(VoidQueue *q);
void VoidQueuePush(VoidQueue *q, void* val);
void* VoidQueuePeek(VoidQueue *q);
void* VoidQueuePop(VoidQueue *q);

#endif
