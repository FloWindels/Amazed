/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** graph.h
*/

#include "amazed.h"

#ifndef GRAPH_H_
    #define GRAPH_H_

// Graph creation and management functions
maze_t *init_maze(int max_rooms);
void free_maze(maze_t *maze);
int add_room(maze_t *maze, const char *name, int x_y[2], bool start_end[2]);
int find_room_by_name(maze_t *maze, const char *name);
int validate_maze(maze_t *maze);

// Matrix operations
int init_adjacency_matrix(maze_t *maze);
int add_connection(maze_t *maze, int room1_idx, int room2_idx);
int add_connection_by_name(maze_t *maze, const char *name1, const char *name2);
int are_rooms_connected(maze_t *maze, int room1_idx, int room2_idx);
int get_room_connections_count(maze_t *maze, int room_idx);

#endif
