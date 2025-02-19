#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

struct Queue
{
    int items[MAX_SIZE];
    int front;
    int rear;
};

void initializeQueue(struct Queue* p_queue)
{
    p_queue->front = -1;
    p_queue->rear = 0;
}

int is_empty(struct Queue* p_queue)
{
    return (p_queue->front == p_queue->rear - 1);
}

int is_full(struct Queue* p_queue)
{
    return (p_queue->rear == MAX_SIZE);
}

void enqueue(struct Queue* p_queue, int value)
{
    if(is_full(p_queue))
    {
        puts("Queue is Full");
        return;
    }
    p_queue->items[p_queue->rear] = value;
    p_queue->rear++;
}

void dequeue(struct Queue* p_queue, int* dequeue_element)
{
    if(is_empty(p_queue))
    {
        puts("Queue is Empty");
        return;
    }
    *dequeue_element = p_queue->items[p_queue->front];
    p_queue->front++;
}

int peek(struct stack* p_queue)
{
    if(is_empty(p_queue))
    {
        puts("Queue is Empty!!");
        return (-1);
    }
    return (p_queue->items[p_queue->front + 1]);
}