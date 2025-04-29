/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_bfs.c
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include "amazed.h"
#include "algorithm.h"

Test(bfs_shortest_path, finds_path_between_connected_nodes)
{
    maze_t maze;
    maze.num_rooms = 4;
    maze.matrix = malloc(sizeof(int *) * 4);
    for (int i = 0; i < 4; i++) {
        maze.matrix[i] = calloc(4, sizeof(int));
    }

    maze.matrix[0][1] = 1;
    maze.matrix[1][0] = 1;
    maze.matrix[1][2] = 1;
    maze.matrix[2][1] = 1;
    maze.matrix[2][3] = 1;
    maze.matrix[3][2] = 1;

    int *pred = bfs_shortest_path(&maze, 0, 3);

    cr_assert_not_null(pred);
    cr_assert_eq(pred[3], 2);
    cr_assert_eq(pred[2], 1);
    cr_assert_eq(pred[1], 0);
    cr_assert_eq(pred[0], -1);

    free(pred);
    for (int i = 0; i < 4; i++)
        free(maze.matrix[i]);
    free(maze.matrix);
}

Test(bfs_shortest_path, returns_null_if_unreachable)
{
    maze_t maze;
    maze.num_rooms = 3;
    maze.matrix = malloc(sizeof(int *) * 3);
    for (int i = 0; i < 3; i++)
        maze.matrix[i] = calloc(3, sizeof(int));

    int *pred = bfs_shortest_path(&maze, 0, 2);
    cr_assert_null(pred);

    for (int i = 0; i < 3; i++)
        free(maze.matrix[i]);
    free(maze.matrix);
}

Test(bfs_shortest_path, returns_empty_path_if_same_start_end)
{
    maze_t maze;
    maze.num_rooms = 2;
    maze.matrix = malloc(sizeof(int *) * 2);
    for (int i = 0; i < 2; i++)
        maze.matrix[i] = calloc(2, sizeof(int));

    int *pred = bfs_shortest_path(&maze, 1, 1);
    cr_assert_not_null(pred);
    for (int i = 0; i < 2; i++)
        cr_assert_eq(pred[i], -1);

    free(pred);
    for (int i = 0; i < 2; i++)
        free(maze.matrix[i]);
    free(maze.matrix);
}

Test(bfs_shortest_path, returns_null_on_invalid_indices)
{
    maze_t maze;
    maze.num_rooms = 2;
    maze.matrix = malloc(sizeof(int *) * 2);
    for (int i = 0; i < 2; i++)
        maze.matrix[i] = calloc(2, sizeof(int));

    cr_assert_null(bfs_shortest_path(&maze, -1, 1));
    cr_assert_null(bfs_shortest_path(&maze, 0, 2));
    cr_assert_null(bfs_shortest_path(NULL, 0, 1));

    for (int i = 0; i < 2; i++)
        free(maze.matrix[i]);
    free(maze.matrix);
}
