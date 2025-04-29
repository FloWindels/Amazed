/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_graph.c
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "amazed.h"
#include "my.h"

maze_t *init_maze(int max_rooms);
int add_room(maze_t *maze, const char *name, int x_y[2], bool start_end[2]);
int find_room_by_name(maze_t *maze, const char *name);
int validate_maze(maze_t *maze);

Test(init_maze, returns_non_null_with_valid_allocation)
{
    maze_t *maze = init_maze(10);
    cr_assert_not_null(maze);
    cr_assert_not_null(maze->rooms);
    cr_assert_eq(maze->num_rooms, 0);
    cr_assert_eq(maze->start_idx, -1);
    cr_assert_eq(maze->end_idx, -1);
    free(maze->rooms);
    free(maze);
}

Test(add_room, adds_room_correctly)
{
    maze_t *maze = init_maze(10);
    int pos[2] = {1, 2};
    bool start_end[2] = {true, false};

    int index = add_room(maze, "StartRoom", pos, start_end);
    cr_assert_eq(index, 0);
    cr_assert_str_eq(maze->rooms[0].name, "StartRoom");
    cr_assert_eq(maze->rooms[0].x, 1);
    cr_assert_eq(maze->rooms[0].y, 2);
    cr_assert(maze->rooms[0].is_start);
    cr_assert_eq(maze->start_idx, 0);

    free(maze->rooms[0].name);
    free(maze->rooms);
    free(maze);
}

Test(find_room_by_name, finds_existing_room)
{
    maze_t *maze = init_maze(10);
    int pos[2] = {0, 0};
    bool start_end[2] = {false, false};

    add_room(maze, "RoomA", pos, start_end);
    add_room(maze, "RoomB", pos, start_end);

    int idx = find_room_by_name(maze, "RoomB");
    cr_assert_eq(idx, 1);

    for (int i = 0; i < maze->num_rooms; i++)
        free(maze->rooms[i].name);
    free(maze->rooms);
    free(maze);
}

Test(find_room_by_name, returns_minus1_if_not_found)
{
    maze_t *maze = init_maze(5);
    cr_assert_eq(find_room_by_name(maze, "Unknown"), -1);
    free(maze->rooms);
    free(maze);
}

Test(validate_maze, returns_1_if_valid)
{
    maze_t *maze = init_maze(3);
    int pos[2] = {0, 0};
    bool start_end1[2] = {true, false};
    bool start_end2[2] = {false, true};

    add_room(maze, "Start", pos, start_end1); 
    add_room(maze, "End", pos, start_end2);

    maze->matrix = malloc(sizeof(int *) * 2);
    for (int i = 0; i < 2; i++)
        maze->matrix[i] = calloc(2, sizeof(int));

    maze->matrix[0][1] = 1;
    maze->num_rooms = 2;

    cr_assert_eq(validate_maze(maze), 1);

    for (int i = 0; i < 2; i++)
        free(maze->matrix[i]);
    free(maze->matrix);
    for (int i = 0; i < maze->num_rooms; i++)
        free(maze->rooms[i].name);
    free(maze->rooms);
    free(maze);
}

Test(validate_maze, returns_0_on_missing_matrix)
{
    maze_t *maze = init_maze(3);
    maze->start_idx = 0;
    maze->end_idx = 1;
    maze->num_rooms = 2;
    cr_assert_eq(validate_maze(maze), 0);
    free(maze->rooms);
    free(maze);
}
