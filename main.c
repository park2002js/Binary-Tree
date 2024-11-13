#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "queue.h"

int main() {
    Stack s;
    Queue q;
    StackInit(&s);
    QueueInit(&q);

    // Push operations.
    for (int i = 0; i < 26; i++) {
        StackPush(&s, 'A'+i);
	QueuePush(&q, 'A'+i);
    }

    printf("Stack size: %d\n", s.sz);
    printf("Queue size: %d\n", q.sz);

    // Pop operations.
    puts("Stack | Queue");
    for (int i = 0; i < 26; i++)
        printf("%c     | %c\n", StackPop(&s), QueuePop(&q));

    printf("Stack size: %d\n", s.sz);
    printf("Queue size: %d\n", q.sz);

    return 0;
}
