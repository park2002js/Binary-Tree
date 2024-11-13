#include <stdlib.h>

#include "node.h"

Node *NodeNew(int val) {
    Node *n = malloc(sizeof(Node));
    n->val = val;
    n->next = NULL;
    return n;
}
