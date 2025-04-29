/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** graph.c
*/

#include <stdlib.h>
#include <stdbool.h>

#include "amazed.h"
#include "my.h"

static int validate_connection(maze_t *maze, int *has_connection, int i)
{
    for (int j = 0; j < maze->num_rooms; j++) {
        if (i != j && maze->matrix[i][j]) {
            *has_connection = 1;
            break;
        }
    }
    if (*has_connection)
        return 1;
    return 0;
}

maze_t *init_maze(int max_rooms)
{
    maze_t *maze = malloc(sizeof(maze_t));
    room_t *rooms = malloc(sizeof(room_t) * max_rooms);

    if (!maze)
        return NULL;
    if (!rooms) {
        free(maze);
        return NULL;
    }
    maze->rooms = rooms;
    maze->num_rooms = 0;
    maze->start_idx = -1;
    maze->end_idx = -1;
    maze->num_robots = 0;
    maze->matrix = NULL;
    return maze;
}

int validate_maze(maze_t *maze)
{
    int has_connection = 0;

    if (!maze)
        return 0;
    if (maze->start_idx == -1 || maze->end_idx == -1)
        return 0;
    if (maze->num_rooms == 0)
        return 0;
    if (!maze->matrix)
        return 0;
    for (int i = 0; i < maze->num_rooms; i++) {
        if (!validate_connection(maze, &has_connection, i))
            return 0;
    }
    if (!has_connection)
        return 0;
    return 1;
}

int add_room(maze_t *maze, const char *name, int x_y[2], bool start_end[2])
{
    int index = maze->num_rooms;

    if (maze->num_rooms >= MAX_ROOMS)
        return -1;
    maze->rooms[index].name = my_strdup(name);
    if (!maze->rooms[index].name)
        return -1;
    maze->rooms[index].x = x_y[0];
    maze->rooms[index].y = x_y[1];
    maze->rooms[index].is_start = start_end[0];
    maze->rooms[index].is_end = start_end[1];
    maze->rooms[index].index = index;
    if (start_end[0])
        maze->start_idx = index;
    if (start_end[1])
        maze->end_idx = index;
    maze->num_rooms++;
    return index;
}

int find_room_by_name(maze_t *maze, const char *name)
{
    for (int i = 0; i < maze->num_rooms; i++) {
        if (my_strcmp(maze->rooms[i].name, name) == 0)
            return i;
    }
    return -1;
}
