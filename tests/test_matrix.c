/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_matrix.c
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "amazed.h"
#include "graph.h"
#include "my.h"

int init_adjacency_matrix(maze_t *maze);
int add_connection(maze_t *maze, int room1_idx, int room2_idx);
int add_connection_by_name(maze_t *maze, const char *name1, const char *name2);
int are_rooms_connected(maze_t *maze, int room1_idx, int room2_idx);
int get_room_connections_count(maze_t *maze, int room_idx);

Test(init_adjacency_matrix, allocates_matrix_successfully)
{
    maze_t maze;
    maze.num_rooms = 3;
    int result = init_adjacency_matrix(&maze);

    cr_assert_eq(result, 0);
    cr_assert_not_null(maze.matrix);
    for (int i = 0; i < maze.num_rooms; i++)
        cr_assert_not_null(maze.matrix[i]);

    for (int i = 0; i < maze.num_rooms; i++)
        free(maze.matrix[i]);
    free(maze.matrix);
}

Test(add_connection, connects_two_rooms)
{
    maze_t maze;
    maze.num_rooms = 2;
    init_adjacency_matrix(&maze);

    int result = add_connection(&maze, 0, 1);
    cr_assert_eq(result, 0);
    cr_assert_eq(maze.matrix[0][1], 1);
    cr_assert_eq(maze.matrix[1][0], 1);

    for (int i = 0; i < maze.num_rooms; i++)
        free(maze.matrix[i]);
    free(maze.matrix);
}

Test(add_connection_by_name, connects_rooms_using_names)
{
    maze_t *maze = init_maze(3);
    int pos[2] = {0, 0};
    bool se[2] = {false, false};

    add_room(maze, "A", pos, se);
    add_room(maze, "B", pos, se);
    maze->num_rooms = 2;
    init_adjacency_matrix(maze);

    int result = add_connection_by_name(maze, "A", "B");
    cr_assert_eq(result, 0);
    cr_assert_eq(maze->matrix[0][1], 1);
    cr_assert_eq(maze->matrix[1][0], 1);

    for (int i = 0; i < maze->num_rooms; i++) {
        free(maze->rooms[i].name);
        free(maze->matrix[i]);
    }
    free(maze->matrix);
    free(maze->rooms);
    free(maze);
}

Test(are_rooms_connected, returns_true_if_connected)
{
    maze_t maze;
    maze.num_rooms = 2;
    init_adjacency_matrix(&maze);
    maze.matrix[0][1] = 1;

    cr_assert_eq(are_rooms_connected(&maze, 0, 1), 1);
    cr_assert_eq(are_rooms_connected(&maze, 1, 0), 0);

    for (int i = 0; i < maze.num_rooms; i++)
        free(maze.matrix[i]);
    free(maze.matrix);
}

Test(get_room_connections_count, counts_connections_correctly)
{
    maze_t maze;
    maze.num_rooms = 3;
    init_adjacency_matrix(&maze);
    maze.matrix[0][1] = 1;
    maze.matrix[0][2] = 1;

    cr_assert_eq(get_room_connections_count(&maze, 0), 2);
    cr_assert_eq(get_room_connections_count(&maze, 1), 0);

    for (int i = 0; i < maze.num_rooms; i++)
        free(maze.matrix[i]);
    free(maze.matrix);
}
