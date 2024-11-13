#include <stdlib.h>

#include "node.h"
#include "stack.h"

void StackInit(Stack *s) {
    s->top = NULL;
    s->sz = 0;
}

void StackPush(Stack *s, int val) {
    Node *n = NodeNew(val);
    n->next = s->top;
    s->top = n;
    s->sz++;
}

int StackPeek(Stack *s) {
    return s->top->val;
}

int StackPop(Stack *s) {
    Node *n = s->top;
    int val = n->val;
    s->top = s->top->next;
    s->sz--;
    free(n);
    return val;
}
