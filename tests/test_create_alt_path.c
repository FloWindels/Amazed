/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_create_alt_path.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "amazed.h"
#include <stdlib.h>

int create_alt_path(robot_t *robot, maze_t *maze,
    int current_alt_room[2], int *new_pred);

Test(create_alt_path, creates_valid_path)
{
    maze_t maze = {
        .end_idx = 4
    };
    robot_t robot = {
        .robot_id = 1,
        .path = NULL,
        .path_length = 0,
        .path_position = 0
    };

    int *pred = malloc(sizeof(int) * 5);
    pred[0] = -1;
    pred[1] = 0;
    pred[2] = 1;
    pred[3] = 2;
    pred[4] = 3;

    int alt_room[2] = {0, 1};

    int ret = create_alt_path(&robot, &maze, alt_room, pred);
    cr_assert_eq(ret, 1);
    cr_assert_eq(robot.path_length, 5);
    cr_assert_eq(robot.path[0], 0);
    cr_assert_eq(robot.path[1], 1);
    cr_assert_eq(robot.path[2], 2);
    cr_assert_eq(robot.path[3], 3);
    cr_assert_eq(robot.path[4], 4);
    free(robot.path);
}

Test(create_alt_path, fails_if_path_broken)
{
    maze_t maze = {
        .end_idx = 4
    };
    robot_t robot = {0};

    int *pred = malloc(sizeof(int) * 5);
    pred[0] = -1;
    pred[1] = 0;
    pred[2] = 1;
    pred[3] = -1;
    pred[4] = 3;

    int alt_room[2] = {0, 1};

    int ret = create_alt_path(&robot, &maze, alt_room, pred);
    cr_assert_eq(ret, -1);
}

