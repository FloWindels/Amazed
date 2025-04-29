/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** matrix.c
*/

#include <stdlib.h>

#include "amazed.h"
#include "graph.h"
#include "my.h"

static void free_matrix(maze_t *maze)
{
    if (!maze->matrix)
        return;
    for (int i = 0; i < maze->num_rooms; i++)
        free(maze->matrix[i]);
    free(maze->matrix);
    maze->matrix = NULL;
}

int init_adjacency_matrix(maze_t *maze)
{
    maze->matrix = malloc(sizeof(int *) * maze->num_rooms);
    if (!maze->matrix)
        return -1;
    for (int i = 0; i < maze->num_rooms; i++) {
        maze->matrix[i] = malloc(sizeof(int) * maze->num_rooms);
        if (!maze->matrix[i]) {
            free_matrix(maze);
            return -1;
        }
    }
    return 0;
}

int add_connection(maze_t *maze, int room1_idx, int room2_idx)
{
    if (!maze || !maze->matrix)
        return -1;
    if (room1_idx < 0 || room1_idx >= maze->num_rooms ||
        room2_idx < 0 || room2_idx >= maze->num_rooms)
        return -1;
    maze->matrix[room1_idx][room2_idx] = 1;
    maze->matrix[room2_idx][room1_idx] = 1;
    return 0;
}

int add_connection_by_name(maze_t *maze, const char *name1, const char *name2)
{
    int idx1 = find_room_by_name(maze, name1);
    int idx2 = find_room_by_name(maze, name2);

    if (idx1 == -1 || idx2 == -1)
        return -1;
    return add_connection(maze, idx1, idx2);
}

int are_rooms_connected(maze_t *maze, int room1_idx, int room2_idx)
{
    if (!maze || !maze->matrix)
        return 0;
    if (room1_idx < 0 || room1_idx >= maze->num_rooms ||
        room2_idx < 0 || room2_idx >= maze->num_rooms)
        return 0;
    return maze->matrix[room1_idx][room2_idx];
}

int get_room_connections_count(maze_t *maze, int room_idx)
{
    int count = 0;

    if (!maze || !maze->matrix)
        return -1;
    if (room_idx < 0 || room_idx >= maze->num_rooms)
        return -1;
    for (int i = 0; i < maze->num_rooms; i++) {
        if (maze->matrix[room_idx][i])
            count++;
    }
    return count;
}
