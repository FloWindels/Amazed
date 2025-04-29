/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_alt_routing.c
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "amazed.h"
#include "algorithm.h"
#include "path_types.h"

int find_best_path_index(path_option_t *paths, int count);

int *bfs_shortest_path(maze_t *maze, int start, int end);

int create_alt_path(robot_t *robot, maze_t *maze, int current_alt_room[2], int *new_pred);

int find_all_paths(maze_t *maze, int start_end[2], path_option_t *paths, int max_paths);

Test(optimize_robot_paths, basic_robot_path_assignment)
{
    maze_t maze = {
        .num_rooms = 3,
        .start_idx = 0,
        .end_idx = 2,
        .matrix = malloc(sizeof(int *) * 3)
    };

    for (int i = 0; i < 3; i++) {
        maze.matrix[i] = calloc(3, sizeof(int));
    }

    simulation_t sim = {
        .num_robots = 1,
        .robots = malloc(sizeof(robot_t)),
        .room_occupancy = calloc(3, sizeof(int))
    };

    int result = optimize_robot_paths(&sim, &maze);
    cr_assert_eq(result, 0);
    cr_assert_not_null(sim.robots[0].path);
    cr_assert_eq(sim.robots[0].path_length, 3);

    free(sim.robots[0].path);
    free(sim.robots);
    free(sim.room_occupancy);
    for (int i = 0; i < 3; i++)
        free(maze.matrix[i]);
    free(maze.matrix);
}

Test(find_alternative_route, returns_valid_alt_when_occupied)
{
    maze_t maze = {
        .num_rooms = 3,
        .start_idx = 0,
        .end_idx = 2,
        .matrix = malloc(sizeof(int *) * 3)
    };

    for (int i = 0; i < 3; i++)
        maze.matrix[i] = calloc(3, sizeof(int));
    maze.matrix[0][1] = 1;
    maze.matrix[1][2] = 1;

    simulation_t sim = {
        .num_robots = 1,
        .robots = malloc(sizeof(robot_t)),
        .room_occupancy = calloc(3, sizeof(int))
    };

    sim.robots[0].current_room = 0;
    sim.robots[0].reached_end = false;
    sim.robots[0].path_position = 0;
    sim.robots[0].path_length = 2;
    sim.robots[0].path = malloc(sizeof(int) * 2);
    sim.robots[0].path[0] = 0;
    sim.robots[0].path[1] = 1;

    sim.room_occupancy[1] = 99;

    int alt = find_alternative_route(&sim, &maze, 0);
    cr_assert_eq(alt, 1);

    free(sim.robots[0].path);
    free(sim.robots[0].path);
    free(sim.robots);
    free(sim.room_occupancy);
    for (int i = 0; i < 3; i++)
        free(maze.matrix[i]);
    free(maze.matrix);
}
