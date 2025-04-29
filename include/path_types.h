/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** path_types.h - Type definitions for pathfinding
*/

#include "algorithm.h"

#ifndef PATH_TYPES_H_
    #define PATH_TYPES_H_

typedef struct {
    int *path;
    int path_length;
    int score;
} path_option_t;

typedef struct {
    queue_t *queue;
    bool **visited;
    int *current_path;
    int *path_len;
} path_resources_t;

typedef struct {
    path_option_t **robot_paths;
    int *path_counts;
    int *path_usage;
} opt_resources_t;

// Functions from pathfinding.c
int find_all_paths(maze_t *maze, int start_end[2],
    path_option_t *paths, int max_paths);
int populate_robot_paths(maze_t *maze, opt_resources_t *res,
    int max_paths, int num_robots);
void free_opt_resources(opt_resources_t *res, int num_robots);
void free_resources(path_resources_t *res, maze_t *maze);
void free_bool_array(bool **array, int size);
void sort_path_options(path_option_t *paths, int count);
void calc_path_scores(path_option_t *paths, int count, int *path_usage);
int find_best_path_index(path_option_t *paths, int count);
int count_path_length(maze_t *maze, int *bfs_path);
int create_alt_path(robot_t *robot, maze_t *maze,
    int current_alt_room[2], int *new_pred);

#endif
