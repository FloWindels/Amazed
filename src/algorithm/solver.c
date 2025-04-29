/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** solver.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "parser.h"
#include "amazed.h"
#include "algorithm.h"
#include "graph.h"
#include "output.h"
#include "my.h"

static int get_nbr_rooms(info_room_t *rooms)
{
    info_room_t *current = rooms;
    int count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

static maze_t *init_maze_from_labyrinth(info_laby_t *laby)
{
    maze_t *maze = NULL;
    int size = get_nbr_rooms(laby->rooms);

    if (!laby)
        return NULL;
    maze = init_maze(size + 1);
    if (!maze)
        return NULL;
    maze->num_robots = laby->nb_robots;
    return maze;
}

static int add_rooms_to_maze(maze_t *maze, info_laby_t *laby)
{
    info_room_t *current_room = NULL;
    int coords[2] = {0, 0};
    bool is_special[2] = {false, false};

    if (!maze || !laby || !laby->rooms)
        return FAILURE;
    current_room = laby->rooms;
    while (current_room) {
        coords[0] = current_room->pos_x;
        coords[1] = current_room->pos_y;
        is_special[0] = (my_strcmp(current_room->name_room,
            laby->name_room_start) == 0);
        is_special[1] = (my_strcmp(current_room->name_room,
            laby->name_room_end) == 0);
        if (add_room(maze, current_room->name_room, coords, is_special) == -1)
            return FAILURE;
        current_room = current_room->next;
    }
    return SUCCESS;
}

static int add_links_to_maze(maze_t *maze, info_laby_t *laby)
{
    link_info_t *current_link = NULL;

    if (!maze || !laby)
        return FAILURE;
    current_link = laby->links;
    while (current_link) {
        if (add_connection_by_name(maze, current_link->act_room,
                current_link->link_room) != 0)
            return FAILURE;
        current_link = current_link->next;
    }
    return SUCCESS;
}

static maze_t *build_maze_from_labyrinth(info_laby_t *laby)
{
    maze_t *maze = init_maze_from_labyrinth(laby);

    if (!maze)
        return NULL;
    if (add_rooms_to_maze(maze, laby) != SUCCESS ||
            init_adjacency_matrix(maze) != 0) {
        free_maze(maze);
        return NULL;
    }
    if (add_links_to_maze(maze, laby) != SUCCESS) {
        free_maze(maze);
        return NULL;
    }
    if (validate_maze(maze) != 1) {
        free_maze(maze);
        return NULL;
    }
    return maze;
}

int solve_and_print_maze(info_laby_t *laby)
{
    maze_t *maze = build_maze_from_labyrinth(laby);
    char ***all_moves = NULL;
    int num_steps = 0;
    int *moves_per_step = NULL;

    if (!laby || !maze)
        return FAILURE;
    all_moves = run_robot_simulation(maze, laby->nb_robots, &num_steps,
        &moves_per_step);
    if (!all_moves || num_steps == 0) {
        free_maze(maze);
        return FAILURE;
    }
    print_robot_moves(all_moves, num_steps, moves_per_step);
    free_moves(all_moves, num_steps, moves_per_step);
    free(moves_per_step);
    free_maze(maze);
    return SUCCESS;
}
