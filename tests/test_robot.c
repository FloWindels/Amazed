/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_perform_simulation_step.c
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include "amazed.h"
#include "algorithm.h"
#include "my.h"


int find_alternative_route(simulation_t *sim, maze_t *maze, int robot_idx);
char *create_move_string(robot_t *robot, char *room_name);

Test(create_move_string, builds_correct_move_string)
{
    robot_t robot = {.robot_id = 42};
    char *str = create_move_string(&robot, "roomA");

    cr_assert_str_eq(str, "P42-roomA");
    free(str);
}

Test(try_move_robot, moves_robot_if_target_unoccupied)
{
    maze_t maze = {.num_rooms = 3, .end_idx = 2};
    maze.matrix = malloc(sizeof(int *) * 3);
    for (int i = 0; i < 3; i++)
        maze.matrix[i] = calloc(3, sizeof(int));

    simulation_t sim = {.num_robots = 1};
    sim.room_occupancy = malloc(sizeof(int) * 3);
    for (int i = 0; i < 3; i++)
        sim.room_occupancy[i] = -1;

    sim.robots = malloc(sizeof(robot_t));
    robot_t *robot = &sim.robots[0];
    robot->robot_id = 1;
    robot->current_room = 0;
    robot->path_length = 3;
    robot->path_position = 0;
    robot->path = malloc(sizeof(int) * 3);
    robot->path[0] = 0;
    robot->path[1] = 1;
    robot->path[2] = 2;

    cr_assert_eq(try_move_robot(&sim, &maze, 0), true);
    cr_assert_eq(robot->current_room, 1);
    cr_assert_eq(robot->path_position, 1);

    free(robot->path);
    free(sim.robots);
    free(sim.room_occupancy);
    for (int i = 0; i < 3; i++) free(maze.matrix[i]);
    free(maze.matrix);
}

Test(perform_simulation_step, returns_step_with_moves)
{
    maze_t maze = {.num_rooms = 2, .end_idx = 1};
    maze.rooms = malloc(sizeof(room_t) * 2);
    maze.rooms[0].name = "start";
    maze.rooms[1].name = "end";

    maze.matrix = malloc(sizeof(int *) * 2);
    for (int i = 0; i < 2; i++)
        maze.matrix[i] = calloc(2, sizeof(int));
    maze.matrix[0][1] = 1;

    simulation_t sim = {.num_robots = 1};
    sim.room_occupancy = malloc(sizeof(int) * 2);
    sim.room_occupancy[0] = 1;
    sim.room_occupancy[1] = -1;

    sim.robots = malloc(sizeof(robot_t));
    sim.robots[0].robot_id = 1;
    sim.robots[0].current_room = 0;
    sim.robots[0].path_length = 2;
    sim.robots[0].path_position = 0;
    sim.robots[0].reached_end = false;
    sim.robots[0].path = malloc(sizeof(int) * 2);
    sim.robots[0].path[0] = 0;
    sim.robots[0].path[1] = 1;

    int count = 0;
    char **step = perform_simulation_step(&sim, &maze, &count);

    cr_assert_not_null(step);
    cr_assert_eq(count, 1);
    cr_assert_str_eq(step[0], "P1-start");

    free(step[0]);
    free(step);
    free(sim.robots[0].path);
    free(sim.robots);
    free(sim.room_occupancy);
    for (int i = 0; i < 2; i++) free(maze.matrix[i]);
    free(maze.matrix);
    free(maze.rooms);
}
