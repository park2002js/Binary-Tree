#ifndef BINARY_TREE_NODE_H_
#define BINARY_TREE_NODE_H_

typedef struct Node {
    void* val;
    struct Node *next;
} Node;

Node *NodeNew(void* val);
#endif
