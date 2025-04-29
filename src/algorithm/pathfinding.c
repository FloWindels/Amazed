/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** pathfinding.c - Core pathfinding algorithm
*/

#include <stdlib.h>
#include <stdbool.h>

#include "algorithm.h"
#include "my.h"
#include "path_types.h"

static bool **init_visited(maze_t *maze)
{
    bool **visited = malloc(sizeof(bool *) * maze->num_rooms);
    int i = 0;

    if (!visited)
        return NULL;
    for (i = 0; i < maze->num_rooms; i++) {
        visited[i] = malloc(sizeof(bool) * maze->num_rooms);
        if (!visited[i]) {
            free_bool_array(visited, i);
            return NULL;
        }
        for (int j = 0; j < maze->num_rooms; j++)
            visited[i][j] = false;
    }
    return visited;
}

static path_resources_t *setup_resources(maze_t *maze)
{
    path_resources_t *res = malloc(sizeof(path_resources_t));

    if (!res)
        return NULL;
    res->queue = init_queue(maze->num_rooms * 10);
    res->visited = init_visited(maze);
    res->current_path = malloc(sizeof(int) * maze->num_rooms);
    res->path_len = malloc(sizeof(int) * maze->num_rooms);
    if (!res->queue || !res->visited || !res->current_path || !res->path_len) {
        free_resources(res, maze);
        return NULL;
    }
    return res;
}

static void init_search(path_resources_t *res, int start)
{
    enqueue(res->queue, start);
    res->current_path[0] = start;
    res->path_len[start] = 1;
    res->visited[start][start] = true;
}

static int helper_extract_path(maze_t *maze, int node, bool **visited)
{
    for (int prev = 0; prev < maze->num_rooms; prev++) {
        if (visited[prev][node] && maze->matrix[prev][node]) {
            node = prev;
            return 1;
        }
    }
    return 0;
}

static int extract_path(path_option_t *path, int current_len[2],
    bool **visited, maze_t *maze)
{
    int node = current_len[0];

    path->path = malloc(sizeof(int) * current_len[1]);
    if (!path->path)
        return 0;
    for (int i = current_len[1] - 1; i >= 0; i--) {
        path->path[i] = node;
        if (helper_extract_path(maze, node, visited))
            break;
    }
    path->path_length = current_len[1];
    return 1;
}

static void process_neighbors(maze_t *maze, int current, int current_len,
    path_resources_t *res)
{
    for (int next = 0; next < maze->num_rooms; next++) {
        if (maze->matrix[current][next] && !res->visited[current][next]) {
            res->visited[current][next] = true;
            enqueue(res->queue, next);
            res->current_path[current_len] = next;
            res->path_len[next] = current_len + 1;
        }
    }
}

int find_all_paths(maze_t *maze, int start_end[2],
    path_option_t *paths, int max_paths)
{
    path_resources_t *res = setup_resources(maze);
    int path_count = 0;
    int current = 0;
    int current_len = 0;

    if (!res)
        return 0;
    init_search(res, start_end[0]);
    while (res->queue->size > 0 && path_count < max_paths) {
        current = dequeue(res->queue);
        current_len = res->path_len[current];
        if (current == start_end[1] && extract_path(&paths[path_count],
                (int[2]){current, current_len}, res->visited, maze))
            path_count++;
        if (current == start_end[1])
            continue;
        process_neighbors(maze, current, current_len, res);
    }
    free_resources(res, maze);
    return path_count;
}

int find_best_path_index(path_option_t *paths, int count)
{
    int best_idx = 0;

    for (int j = 1; j < count; j++)
        if (paths[j].score < paths[best_idx].score)
            best_idx = j;
    return best_idx;
}
