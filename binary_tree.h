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

TreeNode *createTreeNode(int data);
void infixOrder(TreeNode *head);
void prefixOrder(TreeNode *head);
void postfixOrder(TreeNode *head);
void levelOrder(TreeNode *head);
#endif //BINARY_TREE_BINARY_TREE_H
