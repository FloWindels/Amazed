/*
** EPITECH PROJECT, 2024
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** free_resource.c
*/

#include <stdlib.h>
#include <stdbool.h>

#include "algorithm.h"
#include "path_types.h"

static void free_robot_path(path_option_t **robot_paths, int *path_counts,
    int i)
{
    for (int j = 0; j < path_counts[i]; j++)
        if (robot_paths[i][j].path)
            free(robot_paths[i][j].path);
    if (robot_paths[i])
        free(robot_paths[i]);
}

void free_opt_resources(opt_resources_t *res, int num_robots)
{
    if (!res)
        return;
    for (int i = 0; i < num_robots; i++)
        free_robot_path(res->robot_paths, res->path_counts, i);
    free(res->robot_paths);
    free(res->path_counts);
    free(res->path_usage);
}

void free_resources(path_resources_t *res, maze_t *maze)
{
    if (!res)
        return;
    if (res->queue)
        free_queue(res->queue);
    if (res->visited) {
        for (int i = 0; i < maze->num_rooms; i++)
            free(res->visited[i]);
        free(res->visited);
    }
    if (res->current_path)
        free(res->current_path);
    if (res->path_len)
        free(res->path_len);
    free(res);
}

void free_bool_array(bool **array, int size)
{
    if (!array)
        return;
    for (int i = 0; i < size; i++)
        free(array[i]);
    free(array);
}
