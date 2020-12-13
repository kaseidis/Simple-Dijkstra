#include "PriorityQueue.h"
#include <stdio.h>

PriorityQueue init_queue(size_t length)
{
    // Init array space to store min heap
    PriorityQueue q;
    q.queue = malloc(length * sizeof(Node));
    q.length = 0;
    q.max = length;
    return q;
}

void free_queue(PriorityQueue queue)
{
    // Free all array space used
    free(queue.queue);
}

// Helper function to get parent left child and right child
#define leftChild(index) ((index)*2 + 1)

#define rightChild(index) ((index)*2 + 2)

size_t parent(size_t index)
{
    if (index == 0)
        return 0;
    return (index - 1) / 2;
}

// Shift up the item k in heap
void ShiftUp(PriorityQueue q, int k)
{
    while (k > 0 && q.queue[k].dist < q.queue[parent(k)].dist)
    {
        Node tmp = q.queue[parent(k)];
        q.queue[parent(k)] = q.queue[k];
        q.queue[k] = tmp;
        k = parent(k);
    }
}

// Shift down the item k in heap
void ShiftDown(PriorityQueue q, int k)
{
    while (leftChild(k) < q.length)
    {
        // Get j as min child
        int j = leftChild(k);
        if (j + 1 < q.length && q.queue[j].dist > q.queue[j + 1].dist)
            j = rightChild(k);

        if (q.queue[j].dist >= q.queue[k].dist)
            break;
        else
        {
            Node tmp = q.queue[j];
            q.queue[j] = q.queue[k];
            q.queue[k] = tmp;
            k = j;
        }
    }
}

void push_element(PriorityQueue *q, Node node)
{
    // The space is used up
    if (q->length >= q->max)
        return;
    // Add element to heap
    q->queue[q->length] = node;
    q->length++;
    ShiftUp(*q, q->length - 1);
}

Node pop_element(PriorityQueue *q)
{
    // Tring to Pop empty queue
    if (q->length == 0)
    {
        printf("Tring to Pop empty queue\n");
        return q->queue[0];
    }
    // Remove first element to heap, return it
    Node min = q->queue[0];
    if (q->length > 0)
    {
        q->queue[0] = q->queue[q->length - 1];
        q->length--;
        ShiftDown(*q, 0);
    }
    return min;
}