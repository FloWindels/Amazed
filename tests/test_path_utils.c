/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_path_utils.c
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "algorithm.h"
#include "path_types.h"
#include "amazed.h"

Test(calc_path_scores, calculates_scores_correctly)
{
    path_option_t paths[2];
    int usage[5] = {0, 2, 0, 0, 0};

    paths[0].path = (int[]){0, 1, 2};
    paths[0].path_length = 3;

    paths[1].path = (int[]){1, 2, 0};
    paths[1].path_length = 3;

    calc_path_scores(paths, 2, usage);
    cr_assert_eq(paths[0].score, 3 * 100 + 2 * 50);
    cr_assert_eq(paths[1].score, 3 * 100 + 2 * 50);
}

Test(sort_path_options, sorts_by_score_ascending)
{
    path_option_t paths[3];

    for (int i = 0; i < 3; i++) {
        paths[i].path = malloc(sizeof(int) * 2);
        paths[i].path_length = 2;
    }

    paths[0].score = 300;
    paths[1].score = 100;
    paths[2].score = 200;

    sort_path_options(paths, 3);
    cr_assert_eq(paths[0].score, 100);
    cr_assert_eq(paths[1].score, 200);
    cr_assert_eq(paths[2].score, 300);

    for (int i = 0; i < 3; i++)
        free(paths[i].path);
}

Test(count_path_length, returns_correct_length)
{
    maze_t maze = {
        .start_idx = 0,
        .end_idx = 4
    };
    int bfs_path[5] = {-1, 0, 1, 2, 3};

    cr_assert_eq(count_path_length(&maze, bfs_path), 6);
}

Test(count_path_length, returns_minus1_on_invalid_path)
{
    maze_t maze = {
        .start_idx = 0,
        .end_idx = 3
    };
    int bfs_path[4] = {-1, 0, -1, -1};

    cr_assert_eq(count_path_length(&maze, bfs_path), -1);
}

Test(populate_robot_paths, populates_valid_paths)
{
    maze_t maze = {
        .start_idx = 0,
        .end_idx = 2
    };
    opt_resources_t *res = malloc(sizeof(opt_resources_t));
    res->robot_paths = malloc(sizeof(path_option_t *) * 1);
    res->path_counts = malloc(sizeof(int) * 1);

    int ret = populate_robot_paths(&maze, res, 5, 1);
    cr_assert_eq(ret, 0);
    cr_assert_eq(res->path_counts[0], 1);
    cr_assert_eq(res->robot_paths[0][0].path_length, 3);

    free(res->robot_paths[0][0].path);
    free(res->robot_paths[0]);
    free(res->robot_paths);
    free(res->path_counts);
    free(res);
}
