#include <stdio.h>

#include "queue/queue.h"

int main() {
    Queue* q = init_queue();
    int t = 5;

    enqueue(q, (void*)&t);
    int *pt = (int*)dequeue(q);

    printf("Test: %d\n\r", *pt);
    fflush(stdout);

    void* a = dequeue(q);
    a = dequeue(q);
    a = dequeue(q);
    a = dequeue(q);

    destroy_queue(q);
    
    return 0;
}