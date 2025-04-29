/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_pathfinding.c
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include "amazed.h"
#include "path_types.h"
#include "algorithm.h"

Test(find_all_paths, finds_a_path_in_simple_graph)
{
    maze_t maze;
    maze.num_rooms = 3;
    maze.matrix = malloc(sizeof(int *) * 3);
    for (int i = 0; i < 3; i++)
        maze.matrix[i] = calloc(3, sizeof(int));

    maze.matrix[0][1] = 1;
    maze.matrix[1][2] = 1;

    int start_end[2] = {0, 2};
    path_option_t paths[5] = {0};

    int count = find_all_paths(&maze, start_end, paths, 5);
    cr_assert_gt(count, 0);
    cr_assert_gt(paths[0].path_length, 0);
    cr_assert_eq(paths[0].path[0], 2);

    free(paths[0].path);
    for (int i = 0; i < 3; i++)
        free(maze.matrix[i]);
    free(maze.matrix);
}

Test(find_all_paths, returns_zero_if_unreachable)
{
    maze_t maze;
    maze.num_rooms = 2;
    maze.matrix = malloc(sizeof(int *) * 2);
    for (int i = 0; i < 2; i++)
        maze.matrix[i] = calloc(2, sizeof(int));

    int start_end[2] = {0, 1};
    path_option_t paths[2] = {0};

    int count = find_all_paths(&maze, start_end, paths, 2);
    cr_assert_eq(count, 0);

    for (int i = 0; i < 2; i++)
        free(maze.matrix[i]);
    free(maze.matrix);
}

Test(find_best_path_index, returns_index_of_lowest_score)
{
    path_option_t paths[3];
    paths[0].score = 300;
    paths[1].score = 100;
    paths[2].score = 200;

    int best = find_best_path_index(paths, 3);
    cr_assert_eq(best, 1);
}
