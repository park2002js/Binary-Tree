#ifndef BINARY_TREE_BINARY_TREE_H
#define BINARY_TREE_BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *TreeNodeNew(int data);
void InfixOrder(TreeNode *head);
void PrefixOrder(TreeNode *head);
void PostfixOrder(TreeNode *head);
void LevelOrder(TreeNode *head);

#endif //BINARY_TREE_BINARY_TREE_H
