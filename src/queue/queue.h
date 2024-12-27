#include <cstdlib>

typedef struct _Queue {
    struct _Node *head;
    struct _Node *tail;
} Queue;

typedef struct _Node {
    struct _Node* next;
    void* value;
} Node;

void enqueue(Queue* q, void* val);
void* dequeue(Queue* q);
Queue* init_queue();
void destroy_queue(Queue* q);