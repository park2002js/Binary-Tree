#include <stdlib.h>

#include "node.h"
#include "queue.h"

void VoidQueueInit(VoidQueue *q) {
    q->front = NULL;
    q->back = NULL;
    q->sz = 0;
}

void VoidQueuePush(VoidQueue *q, void* val) {
    VoidNode *n = VoidNodeNew(val);
    if (q->back)
        q->back->next = n;
    else
        q->front = n;
    q->back = n;
    q->sz++;
}

void* VoidQueuePeek(VoidQueue *q) {
    return q->front->val;
}

void* VoidQueuePop(VoidQueue *q) {
    if (q->front == NULL) {
        return NULL;
    }

    VoidNode *n = q->front;
    void *val = n->val;
    q->front = q->front->next;
    if (!q->front)
        q->back = NULL;
    q->sz--;
    free(n);
    return val;
}
