/*
** EPITECH PROJECT, 2024
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** simulation.c
*/

#include <stdlib.h>

#include "amazed.h"
#include "algorithm.h"

static char ***allocate_simulation_memory(simulation_t *sim,
    int **moves_per_step)
{
    int max_steps = 1000;
    char ***all_moves = malloc(sizeof(char **) * max_steps);

    if (!all_moves) {
        free_simulation(sim);
        return NULL;
    }
    *moves_per_step = malloc(sizeof(int) * max_steps);
    if (!*moves_per_step) {
        free(all_moves);
        free_simulation(sim);
        return NULL;
    }
    for (int i = 0; i < max_steps; i++) {
        all_moves[i] = NULL;
        (*moves_per_step)[i] = 0;
    }
    return all_moves;
}

static bool all_robots_at_end(simulation_t *sim)
{
    for (int i = 0; i < sim->num_robots; i++) {
        if (!sim->robots[i].reached_end)
            return false;
    }
    return true;
}

static simulation_t *allocate_simulation(maze_t *maze, int num_robots)
{
    simulation_t *sim = malloc(sizeof(simulation_t));

    if (!sim)
        return NULL;
    sim->robots = malloc(sizeof(robot_t) * num_robots);
    if (!sim->robots) {
        free(sim);
        return NULL;
    }
    sim->room_occupancy = malloc(sizeof(int) * maze->num_rooms);
    if (!sim->room_occupancy) {
        free(sim->robots);
        free(sim);
        return NULL;
    }
    return sim;
}

simulation_t *init_simulation(maze_t *maze, int num_robots)
{
    simulation_t *sim = allocate_simulation(maze, num_robots);

    if (!sim)
        return NULL;
    for (int i = 0; i < maze->num_rooms; i++)
        sim->room_occupancy[i] = -1;
    sim->room_occupancy[maze->start_idx] = -2;
    sim->room_occupancy[maze->end_idx] = -2;
    for (int i = 0; i < num_robots; i++) {
        sim->robots[i].robot_id = i + 1;
        sim->robots[i].current_room = maze->start_idx;
        sim->robots[i].path = NULL;
        sim->robots[i].path_length = 0;
        sim->robots[i].path_position = 0;
        sim->robots[i].reached_end = false;
    }
    sim->num_robots = num_robots;
    sim->moves_count = 0;
    return sim;
}

char ***run_robot_simulation(maze_t *maze, int num_robots, int *num_steps,
    int **moves_per_step)
{
    simulation_t *sim = init_simulation(maze, num_robots);
    char ***all_moves = NULL;
    int steps = 0;

    if (!sim)
        return NULL;
    if (optimize_robot_paths(sim, maze) == -1) {
        free_simulation(sim);
        return NULL;
    }
    all_moves = allocate_simulation_memory(sim, moves_per_step);
    if (!all_moves)
        return NULL;
    steps = run_simulation_loop(sim, maze, all_moves, moves_per_step);
    *num_steps = steps;
    free_simulation(sim);
    return all_moves;
}

int run_simulation_loop(simulation_t *sim, maze_t *maze, char ***all_moves,
    int **moves_per_step)
{
    int step = 0;
    int move_count = 0;
    char **step_moves = NULL;
    int max_steps = 1000;

    if (all_robots_at_end(sim))
        return 0;
    while (!all_robots_at_end(sim) && step < max_steps) {
        move_count = 0;
        step_moves = perform_simulation_step(sim, maze, &move_count);
        if (move_count == 0 && step == 0)
            return 0;
        if (move_count == 0)
            break;
        all_moves[step] = step_moves;
        (*moves_per_step)[step] = move_count;
        step++;
    }
    return step;
}
