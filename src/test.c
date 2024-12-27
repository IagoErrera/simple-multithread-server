#include <stdio.h>

#include "queue/queue.h"

int main() {
    Queue* q = init_queue();
    int t = 5;

    enqueue(q, (void*)&t);
    int *pt = (int*)dequeue(q);

    printf("Test: %d\n\r", *pt);
    fflush(stdout);

    free(q);

    return 0;
}