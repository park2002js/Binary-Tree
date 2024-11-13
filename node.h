#ifndef BINARY_TREE_NODE_H_
#define BINARY_TREE_NODE_H_

typedef struct Node {
    int val;
    struct Node *next;
} Node;

Node *NodeNew(int val);

#endif
