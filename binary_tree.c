#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

int precedence(int op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

TreeNode *createTreeNode(int data) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

void infixOrder(TreeNode *head) {
    if (head) {
        infixOrder(head->left);
        printf("%c ", head->data);
        infixOrder(head->right);
    }
}

void prefixOrder(TreeNode* head) {
    if (head) {
        printf("%c ", head->data);
        prefixOrder(head->left);
        prefixOrder(head->right);
    }
}

void postfixOrder(TreeNode* head) {
    if (head) {
        postfixOrder(head->left);
        postfixOrder(head->right);
        printf("%c ", head->data);
    }
}

void levelOrder(TreeNode* head) {
    if (!head) {
        return;
    }
    Queue q;
    QueueInit(&q);
    QueuePush(&q, head);

    while (head != NULL) {
        head = (TreeNode*)QueuePop(&q);

        if (head != NULL) {
            printf("%c ", head->data);

            if (head->left != NULL) {
                QueuePush(&q, head->left);
            }
            if (head->right != NULL) {
                QueuePush(&q, head->right);
            }
        }
    }
}