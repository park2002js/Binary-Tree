#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
    Stack operators;
    Stack operands;
    StackInit(&operators);
    StackInit(&operands);

    for (int i = 0; expression[i] != '\0'; i++) {
        char token = expression[i];

        if (token >= '0' && token <= '9') {
            StackPush(&operands, TreeNodeNew(token));
	} else if (token == '(') {
	    StackPush(&operators, TreeNodeNew(token));
        } else if (token == ')') {
            while (operators.sz > 0 && ((TreeNode*) StackPeek(&operators))->data != '(') {
                TreeNode* opNode = (TreeNode*) StackPop(&operators);
                TreeNode* rightOperand = (TreeNode*) StackPop(&operands);
                TreeNode* leftOperand = (TreeNode*) StackPop(&operands);

                opNode->right = rightOperand;
                opNode->left = leftOperand;

                StackPush(&operands, opNode);
            }
            StackPop(&operators);
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (operators.sz > 0 && Precedence(((TreeNode*) StackPeek(&operators))->data) >= Precedence(token)) {
                TreeNode* opNode = (TreeNode*) StackPop(&operators);
                TreeNode* rightOperand = (TreeNode*) StackPop(&operands);
                TreeNode* leftOperand = (TreeNode*) StackPop(&operands);

                opNode->right = rightOperand;
                opNode->left = leftOperand;

                StackPush(&operands, opNode);
            }
            TreeNode* opNode = TreeNodeNew(token);
            StackPush(&operators, opNode);
        }
    }

    while (operators.sz > 0) {
        TreeNode* opNode = (TreeNode*) StackPop(&operators);
        TreeNode* rightOperand = (TreeNode*) StackPop(&operands);
        TreeNode* leftOperand = (TreeNode*) StackPop(&operands);

        opNode->right = rightOperand;
        opNode->left = leftOperand;

        StackPush(&operands, opNode);
    }

    return (TreeNode*) StackPop(&operands);
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
    
    Queue q;
    QueueInit(&q);
    QueuePush(&q, head);

    while (q.sz > 0) {
        head = (TreeNode*) QueuePop(&q);

        if (head != NULL) {
            printf("%c ", head->data);

            if (head->left != NULL)
                QueuePush(&q, head->left);
            
            if (head->right != NULL)
                QueuePush(&q, head->right);
        }
    }
}
