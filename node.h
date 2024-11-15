#ifndef BINARY_TREE_NODE_H_
#define BINARY_TREE_NODE_H_

typedef struct IntNode {
    int val;
    struct IntNode *next;
} IntNode;

typedef struct VoidNode {
    void* val;
    struct VoidNode *next;
} VoidNode;

IntNode *IntNodeNew(int val);
VoidNode *VoidNodeNew(void* val);

#endif
