/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** amazed.h
*/

#include <stdbool.h>

#ifndef AMAZED_H_
    #define AMAZED_H_

    #define MAX_ROOMS 10000
    #define FAILURE 84
    #define SUCCESS 0

typedef struct {
    char *name;         // Room name (could be any string)
    int x, y;           // Coordinates
    bool is_start;      // true if start room, false otherwise
    bool is_end;        // true if end room, false otherwise
    int index;          // Index in the rooms array for quick reference
} room_t;

typedef struct {
    room_t *rooms;      // Array of all rooms
    int **matrix;       // Adjacency matrix
    int num_rooms;      // Number of rooms
    int start_idx;      // Index of start room
    int end_idx;        // Index of end room
    int num_robots;     // Number of robots
} maze_t;

typedef struct {
    int robot_id;           // Robot identifier
    int current_room;       // Current room index
    int *path;              // Path this robot should follow
    int path_length;        // Length of the path
    int path_position;      // Current position in the path
    bool reached_end;       // Whether the robot has reached the end
} robot_t;

#endif
