/*
** EPITECH PROJECT, 2024
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** path_utils.c
*/

#include <stdlib.h>

#include "path_types.h"
#include "algorithm.h"

static int calculate_path_score(int *path, int path_length, int *path_usage)
{
    int score = path_length * 100;
    int room = 0;

    for (int i = 0; i < path_length; i++) {
        room = path[i];
        if (path_usage && path_usage[room] > 0)
            score += path_usage[room] * 50;
    }
    return score;
}

static void sort_path(path_option_t *paths, int j, int k)
{
    path_option_t temp;

    if (paths[j].score > paths[k].score) {
        temp = paths[j];
        paths[j] = paths[k];
        paths[k] = temp;
    }
}

void sort_path_options(path_option_t *paths, int count)
{
    for (int j = 0; j < count - 1; j++) {
        for (int k = j + 1; k < count; k++) {
            sort_path(paths, j, k);
        }
    }
}

void calc_path_scores(path_option_t *paths, int count, int *path_usage)
{
    for (int j = 0; j < count; j++) {
        paths[j].score = calculate_path_score(
            paths[j].path, paths[j].path_length, path_usage);
    }
}

int count_path_length(maze_t *maze, int *bfs_path)
{
    int path_len = 0;
    int current = maze->end_idx;

    while (current != maze->start_idx) {
        path_len++;
        current = bfs_path[current];
        if (current == -1)
            return -1;
    }
    return path_len + 2;
}

int populate_robot_paths(maze_t *maze, opt_resources_t *res,
    int max_paths, int num_robots)
{
    for (int i = 0; i < num_robots; i++) {
        res->robot_paths[i] = malloc(sizeof(path_option_t) * max_paths);
        if (!res->robot_paths[i]) {
            res->path_counts[i] = 0;
            continue;
        }
        res->path_counts[i] = find_all_paths(maze, (int[2]){maze->start_idx,
            maze->end_idx}, res->robot_paths[i], max_paths);
        calc_path_scores(res->robot_paths[i], res->path_counts[i], NULL);
        sort_path_options(res->robot_paths[i], res->path_counts[i]);
    }
    return 0;
}
