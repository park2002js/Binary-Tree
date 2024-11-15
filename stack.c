#include <stdlib.h>

#include "node.h"
#include "stack.h"

void StackInit(Stack *s) {
    s->top = NULL;
    s->sz = 0;
}

void StackPush(Stack *s, void *val) {
    Node *n = NodeNew(val);
    n->next = s->top;
    s->top = n;
    s->sz++;
}

void* StackPeek(Stack *s) {
    return s->top->val;
}

void *StackPop(Stack *s) {
    Node *n = s->top;
    void* val = n->val;
    s->top = s->top->next;
    s->sz--;
    free(n);
    return val;
}
