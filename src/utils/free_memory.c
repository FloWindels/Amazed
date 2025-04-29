/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** free_memory.c - Memory management functions
*/

#include <stdlib.h>

#include "algorithm.h"
#include "parser.h"
#include "my.h"

static void free_links(link_info_t *links)
{
    link_info_t *current = links;
    link_info_t *next = NULL;

    while (current) {
        next = current->next;
        free(current->act_room);
        free(current->link_room);
        free(current);
        current = next;
    }
}

static void free_rooms(info_room_t *rooms)
{
    info_room_t *current = rooms;
    info_room_t *next = NULL;

    while (current) {
        next = current->next;
        free(current->name_room);
        free(current);
        current = next;
    }
}

static void free_moves_per_step(char ***moves, int *moves_per_step, int i)
{
    for (int j = 0; j < moves_per_step[i]; j++)
        free(moves[i][j]);
    free(moves[i]);
}

void free_labyrinth(info_laby_t *laby)
{
    if (!laby)
        return;
    if (laby->name_room_start)
        free(laby->name_room_start);
    if (laby->name_room_end)
        free(laby->name_room_end);
    if (laby->rooms)
        free_rooms(laby->rooms);
    if (laby->links)
        free_links(laby->links);
}

void free_word_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

void free_moves(char ***moves, int num_steps, int *moves_per_step)
{
    if (!moves)
        return;
    for (int i = 0; i < num_steps; i++) {
        if (moves[i]) {
            free_moves_per_step(moves, moves_per_step, i);
        }
    }
    free(moves);
}

void free_simulation(simulation_t *sim)
{
    if (!sim)
        return;
    if (sim->robots) {
        for (int i = 0; i < sim->num_robots; i++)
            free(sim->robots[i].path);
        free(sim->robots);
    }
    free(sim->room_occupancy);
    free(sim);
}

void free_maze(maze_t *maze)
{
    if (!maze)
        return;
    for (int i = 0; i < maze->num_rooms; i++)
        free(maze->rooms[i].name);
    free(maze->rooms);
    if (maze->matrix) {
        for (int i = 0; i < maze->num_rooms; i++)
            free(maze->matrix[i]);
        free(maze->matrix);
    }
    free(maze);
}
