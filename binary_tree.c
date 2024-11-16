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

void TreeFree(TreeNode* head) {
    if (head == NULL) return;

    TreeFree(head->left);
    TreeFree(head->right);

    free(head);
}

TreeNode* CreateExpressionTree(char* expression) {
    IntStack operators;
    IntStack operands;
    IntStackInit(&operators);
    IntStackInit(&operands);

    for (int i = 0; expression[i] != '\0'; i++) {
        char token = expression[i];

        if (token >= '0' && token <= '9') {
            TreeNode* node = TreeNodeNew(token);
            IntStackPush(&operands, (int)(intptr_t)node);
        } else if (token == '(') {
            IntStackPush(&operators, (int)(intptr_t)TreeNodeNew(token));
        } else if (token == ')') {
            while (!IntStackIsEmpty(&operators) &&
                   (char)((TreeNode*)(intptr_t)IntStackPeek(&operators))->data != '(') {
                TreeNode* opNode = (TreeNode*)(intptr_t)IntStackPop(&operators);
                TreeNode* rightOperand = (TreeNode*)(intptr_t)IntStackPop(&operands);
                TreeNode* leftOperand = (TreeNode*)(intptr_t)IntStackPop(&operands);

                opNode->right = rightOperand;
                opNode->left = leftOperand;

                IntStackPush(&operands, (int)(intptr_t)opNode);
            }
            IntStackPop(&operators);
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (!IntStackIsEmpty(&operators) && Precedence((char)((TreeNode*)(intptr_t)IntStackPeek(&operators))->data) >= Precedence(token)) {
                TreeNode* opNode = (TreeNode*)(intptr_t)IntStackPop(&operators);
                TreeNode* rightOperand = (TreeNode*)(intptr_t)IntStackPop(&operands);
                TreeNode* leftOperand = (TreeNode*)(intptr_t)IntStackPop(&operands);

                opNode->right = rightOperand;
                opNode->left = leftOperand;

                IntStackPush(&operands, (int)(intptr_t)opNode);
            }
            TreeNode* opNode = TreeNodeNew(token);
            IntStackPush(&operators, (int)(intptr_t)opNode);
        }
    }

    while (!IntStackIsEmpty(&operators)) {
        TreeNode* opNode = (TreeNode*)(intptr_t)IntStackPop(&operators);
        TreeNode* rightOperand = (TreeNode*)(intptr_t)IntStackPop(&operands);
        TreeNode* leftOperand = (TreeNode*)(intptr_t)IntStackPop(&operands);

        opNode->right = rightOperand;
        opNode->left = leftOperand;

        IntStackPush(&operands, (int)(intptr_t)opNode);
    }

    return (TreeNode*)(intptr_t)IntStackPop(&operands);
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
