/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** bfs.c
*/

#include <stdlib.h>
#include <stdbool.h>

#include "algorithm.h"

static bool *init_bfs_visited(maze_t *maze)
{
    bool *visited = malloc(sizeof(bool) * maze->num_rooms);

    if (!visited)
        return NULL;
    for (int i = 0; i < maze->num_rooms; i++)
        visited[i] = false;
    return visited;
}

static int *init_bfs_pred(maze_t *maze)
{
    int *pred = malloc(sizeof(int) * maze->num_rooms);

    if (!pred)
        return NULL;
    for (int i = 0; i < maze->num_rooms; i++)
        pred[i] = -1;
    return pred;
}

static int helper_init_queue(maze_t *maze, bfs_data_t *data)
{
    data->queue = init_queue(maze->num_rooms);
    if (!data->queue) {
        free(data->visited);
        free(data->pred);
        free(data);
        return -1;
    }
    return 0;
}

static bfs_data_t *init_bfs_data(maze_t *maze)
{
    bfs_data_t *data = malloc(sizeof(bfs_data_t));

    if (!data)
        return NULL;
    data->visited = init_bfs_visited(maze);
    if (!data->visited) {
        free(data);
        return NULL;
    }
    data->pred = init_bfs_pred(maze);
    if (!data->pred) {
        free(data->visited);
        free(data);
        return NULL;
    }
    if (helper_init_queue(maze, data) == -1)
        return NULL;
    data->maze = maze;
    return data;
}

static void free_bfs_data(bfs_data_t *data, bool keep_pred)
{
    if (!data)
        return;
    if (data->queue)
        free_queue(data->queue);
    if (data->visited)
        free(data->visited);
    if (!keep_pred && data->pred)
        free(data->pred);
    free(data);
}

static void process_bfs_node(bfs_data_t *data, int current)
{
    maze_t *maze = data->maze;

    if (!maze || !data->visited || !data->pred || !data->queue)
        return;
    for (int i = 0; i < maze->num_rooms; i++) {
        if (maze->matrix[current][i] && !data->visited[i]) {
            data->visited[i] = true;
            data->pred[i] = current;
            enqueue(data->queue, i);
        }
    }
}

static void run_bfs_algorithm(bfs_data_t *data, int start, int end)
{
    int current = 0;

    if (!data || !data->visited || !data->queue)
        return;
    data->visited[start] = true;
    enqueue(data->queue, start);
    while (data->queue && data->queue->size > 0) {
        current = dequeue(data->queue);
        if (current == end)
            break;
        process_bfs_node(data, current);
    }
}

static int *check_bfs_result(bfs_data_t *data, int start, int end)
{
    int *pred = NULL;

    if (!data || !data->pred)
        return NULL;
    pred = data->pred;
    data->pred = NULL;
    if (pred[end] == -1 && start != end) {
        free(pred);
        return NULL;
    }
    return pred;
}

static int *bfs_helper(maze_t *maze)
{
    int *result = malloc(sizeof(int) * maze->num_rooms);

    if (!result)
        return NULL;
    for (int i = 0; i < maze->num_rooms; i++)
        result[i] = -1;
    return result;
}

int *bfs_shortest_path(maze_t *maze, int start, int end)
{
    int *result = NULL;
    bfs_data_t *data = NULL;

    if (!maze || !maze->matrix || start < 0 || end < 0 ||
        start >= maze->num_rooms || end >= maze->num_rooms)
        return NULL;
    if (start == end) {
        result = bfs_helper(maze);
        return result;
    }
    data = init_bfs_data(maze);
    if (!data)
        return NULL;
    run_bfs_algorithm(data, start, end);
    result = check_bfs_result(data, start, end);
    free_bfs_data(data, true);
    return result;
}
