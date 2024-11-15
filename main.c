#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "stack.h"
#include "queue.h"

int main() {
    Stack s;
    Queue q;
    StackInit(&s);
    QueueInit(&q);

    // Push operations.
    for (int i = 0; i < 26; i++) {
        int *stackVal = malloc(sizeof(int));
        int *queueVal = malloc(sizeof(int));

        *stackVal = 'A' + i;
        *queueVal = 'A' + i;

        StackPush(&s, stackVal);
        QueuePush(&q, queueVal);
    }

    printf("Stack size: %d\n", s.sz);
    printf("Queue size: %d\n", q.sz);

    // Pop operations.
    puts("Stack | Queue");
    for (int i = 0; i < 26; i++) {
        int *stackVal = (int *)StackPop(&s);
        int *queueVal = (int *)QueuePop(&q);
        printf("%c     | %c\n", *stackVal, *queueVal);

        free(stackVal);
        free(queueVal);
    }

    printf("Stack size: %d\n", s.sz);
    printf("Queue size: %d\n", q.sz);

    // TreeNode operations
    TreeNode* root = TreeNodeNew('A');
    root->left = TreeNodeNew('B');
    root->right = TreeNodeNew('C');
    root->left->left = TreeNodeNew('D');
    root->left->right = TreeNodeNew('E');
    root->right->left = TreeNodeNew('F');

    printf("Level-order: ");
    LevelOrder(root);
    printf("\n");

    printf("Infix-order: ");
    InfixOrder(root);
    printf("\n");

    printf("Prefix-order: ");
    PrefixOrder(root);
    printf("\n");

    printf("Postfix-order: ");
    PostfixOrder(root);
    printf("\n");

    return 0;
}
