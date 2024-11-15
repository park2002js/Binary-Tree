#include <stdlib.h>

#include "node.h"

Node *NodeNew(void* val) {
    Node *n = malloc(sizeof(Node));
    n->val = val;
    n->next = NULL;
    return n;
}
