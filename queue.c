#include <stdlib.h>

#include "node.h"
#include "queue.h"

void QueueInit(Queue *q) {
    q->front = NULL;
    q->back = NULL;
    q->sz = 0;
}

void QueuePush(Queue *q, int val) {
    Node *n = NodeNew(val);
    if (q->back)
        q->back->next = n;
    else
        q->front = n;
    q->back = n;
    q->sz++;
}

int QueuePeek(Queue *q) {
    return q->front->val;
}

int QueuePop(Queue *q) {
    Node *n = q->front;
    int val = n->val;
    q->front = q->front->next;
    if (!q->front)
        q->back = NULL;
    q->sz--;
    free(n);
    return val;
}
