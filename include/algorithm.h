/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** algorithm.h
*/

#include "amazed.h"

#ifndef ALGORITHM_H_
    #define ALGORITHM_H_

typedef struct {
    robot_t *robots;
    int num_robots;
    int *room_occupancy;
    int moves_count;
} simulation_t;

typedef struct {
    simulation_t *sim;
    maze_t *maze;
    char **step_moves;
    int robot_idx;
    int *move_count;
} move_data_t;

// Queue structure for BFS
typedef struct {
    int *data;
    int front;
    int rear;
    int size;
    int capacity;
} queue_t;

typedef struct bfs_data {
    bool *visited;
    int *pred;
    queue_t *queue;
    maze_t *maze;
} bfs_data_t;

// Queue operations
queue_t *init_queue(int max_size);
void free_queue(queue_t *queue);
int enqueue(queue_t *queue, int value);
int dequeue(queue_t *queue);

// Simulation operations
simulation_t *init_simulation(maze_t *maze, int num_robots);
void free_simulation(simulation_t *sim);
int run_simulation_loop(simulation_t *sim, maze_t *maze,
    char ***all_moves, int **moves_per_step);
bool try_move_robot(simulation_t *sim, maze_t *maze, int robot_idx);

// BFS operations
int *bfs_shortest_path(maze_t *maze, int start, int end);
int find_alternative_route(simulation_t *sim, maze_t *maze, int robot_idx);

// Robot simulation operations
char **perform_simulation_step(simulation_t *sim, maze_t *maze,
    int *move_count);
char ***run_robot_simulation(maze_t *maze, int num_robots, int *num_steps,
    int **moves_per_step);
int optimize_robot_paths(simulation_t *sim, maze_t *maze);
void free_moves(char ***moves, int num_steps, int *moves_per_step);
move_data_t init_move_data(simulation_t *sim, maze_t *maze,
    char **step_moves, int *move_count);

#endif
