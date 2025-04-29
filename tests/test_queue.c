/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_queue.c
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include "algorithm.h"

Test(init_queue, initializes_correctly)
{
    queue_t *queue = init_queue(5);
    cr_assert_not_null(queue);
    cr_assert_not_null(queue->data);
    cr_assert_eq(queue->front, 0);
    cr_assert_eq(queue->rear, -1);
    cr_assert_eq(queue->size, 0);
    cr_assert_eq(queue->capacity, 5);

    free_queue(queue);
}

Test(enqueue_dequeue, works_in_fifo_order)
{
    queue_t *queue = init_queue(3);

    cr_assert_eq(enqueue(queue, 10), 0);
    cr_assert_eq(enqueue(queue, 20), 0);
    cr_assert_eq(enqueue(queue, 30), 0);
    cr_assert_eq(enqueue(queue, 40), -1);

    cr_assert_eq(dequeue(queue), 10);
    cr_assert_eq(dequeue(queue), 20);
    cr_assert_eq(dequeue(queue), 30);
    cr_assert_eq(dequeue(queue), -1);

    free_queue(queue);
}

Test(queue_wraparound, rear_and_front_wrap_correctly)
{
    queue_t *queue = init_queue(3);
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    cr_assert_eq(dequeue(queue), 1);
    enqueue(queue, 4);
    cr_assert_eq(dequeue(queue), 2);
    cr_assert_eq(dequeue(queue), 3);
    cr_assert_eq(dequeue(queue), 4);
    cr_assert_eq(dequeue(queue), -1);
    free_queue(queue);
}

Test(enqueue_dequeue, handle_null_queue)
{
    cr_assert_eq(enqueue(NULL, 42), -1);
    cr_assert_eq(dequeue(NULL), -1);
}
