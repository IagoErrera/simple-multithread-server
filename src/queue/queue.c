#include "queue.h"

#include <stdio.h>

void enqueue(Queue* q, void* val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = val; 
    node->next = NULL;

    if (q->head == NULL) q->head = node;
    if (q->tail != NULL) q->tail->next = node;
    q->tail = node;
}

void* dequeue(Queue* q) {
    if (q->head == NULL) return NULL;

    void* val = q->head->value;
    Node* node = q->head;

    if (q->head->next == NULL) q->tail = NULL;
    q->head = q->head->next;

    free(node);

    return val;
}

void destroy_queue(Queue* q) {
    while (q->head != NULL)
        dequeue(q);
}

Queue* init_queue() {
    return (Queue*)malloc(sizeof(Queue));
}