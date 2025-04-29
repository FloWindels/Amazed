/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** alt_routing.c - Alternative route finding and path optimization
*/

#include <stdlib.h>
#include <stdbool.h>

#include "algorithm.h"
#include "my.h"
#include "path_types.h"

static int build_bfs_path(robot_t *robot, int *bfs_path,
    int path_len, int start_end_idx[2])
{
    int current = start_end_idx[1];
    int idx = path_len - 1;

    robot->path = malloc(sizeof(int) * path_len);
    if (!robot->path) {
        free(bfs_path);
        return -1;
    }
    robot->path[idx] = current;
    idx -= 1;
    for (; current != start_end_idx[0]; idx--) {
        current = bfs_path[current];
        if (current == -1)
            break;
        robot->path[idx] = current;
    }
    robot->path_length = path_len;
    robot->path_position = 0;
    free(bfs_path);
    return 0;
}

static int process_bfs_path(robot_t *robot, maze_t *maze, int *bfs_path)
{
    int path_len = count_path_length(maze, bfs_path);

    if (path_len == -1) {
        free(bfs_path);
        return -1;
    }
    return build_bfs_path(robot, bfs_path, path_len,
        (int[2]){maze->start_idx, maze->end_idx});
}

static int apply_best_path(robot_t *robot, path_option_t *best_path,
    int *path_usage, maze_t *maze)
{
    int room = 0;

    robot->path = malloc(sizeof(int) * best_path->path_length);
    if (!robot->path)
        return -1;
    for (int j = 0; j < best_path->path_length; j++) {
        robot->path[j] = best_path->path[j];
        room = best_path->path[j];
        if (room != maze->start_idx && room != maze->end_idx)
            path_usage[room]++;
    }
    robot->path_length = best_path->path_length;
    robot->path_position = 0;
    return 0;
}

static int init_opt_resources(simulation_t *sim, maze_t *maze,
    opt_resources_t *resources)
{
    resources->robot_paths = malloc(sizeof(path_option_t *) * sim->num_robots);
    resources->path_counts = malloc(sizeof(int) * sim->num_robots);
    resources->path_usage = malloc(sizeof(int) * maze->num_rooms);
    if (!resources->robot_paths || !resources->path_counts ||
        !resources->path_usage) {
        if (resources->robot_paths)
            free(resources->robot_paths);
        if (resources->path_counts)
            free(resources->path_counts);
        if (resources->path_usage)
            free(resources->path_usage);
        return -1;
    }
    return 0;
}

static int process_robot(simulation_t *sim, maze_t *maze,
    opt_resources_t *res, int i)
{
    int *bfs_path = NULL;
    int best_idx = 0;

    if (res->path_counts[i] == 0) {
        bfs_path = bfs_shortest_path(maze, maze->start_idx, maze->end_idx);
        if (!bfs_path)
            return -1;
        return process_bfs_path(&sim->robots[i], maze, bfs_path);
    }
    calc_path_scores(res->robot_paths[i], res->path_counts[i],
        res->path_usage);
    best_idx = find_best_path_index(res->robot_paths[i],
        res->path_counts[i]);
    return apply_best_path(&sim->robots[i],
        &res->robot_paths[i][best_idx], res->path_usage, maze);
}

static int try_alt_room(simulation_t *sim, maze_t *maze, robot_t *robot, int i)
{
    int *new_pred = NULL;

    if (i == robot->current_room || !maze->matrix[robot->current_room][i])
        return -1;
    if (i == maze->end_idx || sim->room_occupancy[i] == -1) {
        new_pred = bfs_shortest_path(maze, i, maze->end_idx);
        if (!new_pred)
            return -1;
        return create_alt_path(robot, maze,
            (int[2]){robot->current_room, i}, new_pred);
    }
    return -1;
}

static int check_for_alternative(simulation_t *sim, maze_t *maze,
    robot_t *robot)
{
    int result = -1;

    for (int i = 0; i < maze->num_rooms; i++) {
        result = try_alt_room(sim, maze, robot, i);
        if (result != -1)
            return result;
    }
    return -1;
}

int find_alternative_route(simulation_t *sim, maze_t *maze, int robot_idx)
{
    robot_t *robot = &sim->robots[robot_idx];
    int intended_room = 0;
    int result = -1;

    if (robot->reached_end || !robot->path ||
        robot->path_position >= robot->path_length - 1)
        return -1;
    intended_room = robot->path[robot->path_position + 1];
    if (intended_room != maze->end_idx &&
            sim->room_occupancy[intended_room] != -1) {
        result = check_for_alternative(sim, maze, robot);
        if (result != -1)
            return result;
    }
    return result;
}

int optimize_robot_paths(simulation_t *sim, maze_t *maze)
{
    int max_paths_per_robot = 3;
    opt_resources_t res = {0};

    if (init_opt_resources(sim, maze, &res) != 0)
        return -1;
    populate_robot_paths(maze, &res, max_paths_per_robot, sim->num_robots);
    for (int i = 0; i < sim->num_robots; i++) {
        if (process_robot(sim, maze, &res, i) != 0)
            continue;
    }
    free_opt_resources(&res, sim->num_robots);
    return 0;
}
