#ifndef BINARY_TREE_STACK_H_
#define BINARY_TREE_STACK_H_

#include "node.h"

typedef struct IntStack {
    IntNode *top;
    int sz;
} IntStack;

void IntStackInit(IntStack *s);
void IntStackPush(IntStack *s, int val);
int IntStackPeek(IntStack *s);
int IntStackPop(IntStack *s);
int IntStackIsEmpty(IntStack *s);

#endif
