#include <stdlib.h>

#include "node.h"

IntNode *IntNodeNew(int val) {
    IntNode *n = malloc(sizeof(VoidNode));
    n->val = val;
    n->next = NULL;
    return n;
}

VoidNode *VoidNodeNew(void* val) {
    VoidNode *n = malloc(sizeof(VoidNode));
    n->val = val;
    n->next = NULL;
    return n;
}
