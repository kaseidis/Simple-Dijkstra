
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Node.h"
#include <stdlib.h>

typedef struct
{
    Node* queue;
    size_t length;
    size_t max;
} PriorityQueue;

/**
 * Init a new priority queue
 * @param length    Max length of the queue
 */ 
PriorityQueue init_queue(size_t length);

/**
 * Free all mem used in queue
 * @param queue     The Priority Queue.
 */ 
void free_queue(PriorityQueue queue);

/**
 * Push element into priority queue.
 * @param q         The Priority Queue.
 * @param node      The node to be pushed.
 */ 
void push_element(PriorityQueue* q, Node node);

/**
 * Check if it is empty queue
 * @param q         The Priority Queue.
 */ 
#define is_empty(q) ((q).length==0)

/**
 * Pop the min element from priority queue.
 * @param q         The Priority Queue.
 * @return          The min node form queue.
 */ 
Node pop_element(PriorityQueue* q);
#endif