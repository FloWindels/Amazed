/*
** EPITECH PROJECT, 2024
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** queue.c
*/

#include <stdlib.h>

#include "algorithm.h"

queue_t *init_queue(int max_size)
{
    queue_t *queue = malloc(sizeof(queue_t));

    if (!queue)
        return NULL;
    queue->data = malloc(max_size * sizeof(int));
    if (!queue->data) {
        free(queue);
        return NULL;
    }
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = max_size;
    return queue;
}

void free_queue(queue_t *queue)
{
    if (!queue)
        return;
    free(queue->data);
    free(queue);
}

int enqueue(queue_t *queue, int value)
{
    if (!queue || queue->size == queue->capacity)
        return -1;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = value;
    queue->size += 1;
    return 0;
}

int dequeue(queue_t *queue)
{
    int value = 0;

    if (!queue || queue->size == 0)
        return -1;
    value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return value;
}
