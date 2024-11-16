#ifndef BINARY_TREE_STACK_H_
#define BINARY_TREE_STACK_H_

#include "node.h"

typedef struct Stack {
    Node *top;
    int sz;
} Stack;

void StackInit(Stack *s);
void StackPush(Stack *s, void *val);
void *StackPeek(Stack *s);
void *StackPop(Stack *s);

#endif
