#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

int Precedence(int op) {
    if (op == '+' || op == '-')
        return 1;
    
    if (op == '*' || op == '/')
        return 2;
    
    return 0;
}

TreeNode *TreeNodeNew(int data) {
    TreeNode *node = (TreeNode*) malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

void InfixOrder(TreeNode *head) {
    if (head) {
        InfixOrder(head->left);
        printf("%c ", head->data);
        InfixOrder(head->right);
    }
}

void PrefixOrder(TreeNode* head) {
    if (head) {
        printf("%c ", head->data);
        PrefixOrder(head->left);
        PrefixOrder(head->right);
    }
}

void PostfixOrder(TreeNode* head) {
    if (head) {
        PostfixOrder(head->left);
        PostfixOrder(head->right);
        printf("%c ", head->data);
    }
}

void LevelOrder(TreeNode* head) {
    if (!head)
        return;
    
    VoidQueue q;
    VoidQueueInit(&q);
    VoidQueuePush(&q, head);

    while (q.sz > 0) {
        head = (TreeNode*) VoidQueuePop(&q);

        if (head != NULL) {
            printf("%c ", head->data);

            if (head->left != NULL)
                VoidQueuePush(&q, head->left);
            
            if (head->right != NULL)
                VoidQueuePush(&q, head->right);
        }
    }
}
