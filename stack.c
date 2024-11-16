#include <stdlib.h>

#include "node.h"
#include "stack.h"

void IntStackInit(IntStack *s) {
    s->top = NULL;
    s->sz = 0;
}

void IntStackPush(IntStack *s, int val) {
    IntNode *n = IntNodeNew(val);
    n->next = s->top;
    s->top = n;
    s->sz++;
}

int IntStackPeek(IntStack *s) {
    return s->top->val;
}

int IntStackPop(IntStack *s) {
    IntNode *n = s->top;
    int val = n->val;
    s->top = s->top->next;
    s->sz--;
    free(n);
    return val;
}

int IntStackIsEmpty(IntStack *s) {
    return s->top == NULL;
}