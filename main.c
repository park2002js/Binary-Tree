#include "stack.h"
#include "binary_tree.h"

int main() {
    IntStack s;
    IntStackInit(&s);

    // Push operations.
    for (int i = 0; i < 26; i++)
        IntStackPush(&s, 'A'+i);

    printf("Stack size: %d\n", s.sz);

    // Pop operations.
    for (int i = 0; i < 26; i++)
        printf("%c\n", IntStackPop(&s));

    printf("Stack size: %d\n", s.sz);

    // TreeNode operations.
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

    TreeFree(root);

    char expression[] = "3+5*2-8/4";
    TreeNode* exp = CreateExpressionTree(expression);
    printf("Level-order22: ");
    LevelOrder(exp);
    printf("\n");

    printf("Infix-order: ");
    InfixOrder(exp);
    printf("\n");

    printf("Prefix-order: ");
    PrefixOrder(exp);
    printf("\n");

    printf("Postfix-order: ");
    PostfixOrder(exp);
    printf("\n");

    TreeFree(exp);

    return 0;
}
