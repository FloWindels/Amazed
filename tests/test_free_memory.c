/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_free_memory.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "amazed.h"
#include "parser.h"
#include "algorithm.h"
#include <stdlib.h>
#include <string.h>

void free_maze(maze_t *maze);

Test(free_labyrinth, frees_all_fields)
{
    info_laby_t *laby = malloc(sizeof(info_laby_t));
    laby->name_room_start = strdup("start");
    laby->name_room_end = strdup("end");

    info_room_t *room = malloc(sizeof(info_room_t));
    room->name_room = strdup("roomA");
    room->next = NULL;
    laby->rooms = room;

    link_info_t *link = malloc(sizeof(link_info_t));
    link->act_room = strdup("roomA");
    link->link_room = strdup("roomB");
    link->next = NULL;
    laby->links = link;

    free_labyrinth(laby);
    free(laby);
}

Test(free_word_array, frees_array_of_strings)
{
    char **array = malloc(sizeof(char *) * 3);
    array[0] = strdup("word1");
    array[1] = strdup("word2");
    array[2] = NULL;

    free_word_array(array);
}

Test(free_moves, frees_2d_array)
{
    int num_steps = 2;
    int *moves_per_step = malloc(sizeof(int) * 2);
    moves_per_step[0] = 2;
    moves_per_step[1] = 1;

    char ***moves = malloc(sizeof(char **) * 2);

    moves[0] = malloc(sizeof(char *) * 2);
    moves[0][0] = strdup("A1");
    moves[0][1] = strdup("A2");

    moves[1] = malloc(sizeof(char *) * 1);
    moves[1][0] = strdup("B1");

    free_moves(moves, num_steps, moves_per_step);
    free(moves_per_step);
}

Test(free_simulation, frees_simulation_struct)
{
    simulation_t *sim = malloc(sizeof(simulation_t));
    sim->num_robots = 2;
    sim->robots = malloc(sizeof(robot_t) * 2);
    sim->robots[0].path = malloc(sizeof(int) * 3);
    sim->robots[1].path = malloc(sizeof(int) * 2);
    sim->room_occupancy = malloc(sizeof(int) * 10);

    free_simulation(sim);
}

Test(free_maze, frees_maze_struct)
{
    maze_t *maze = malloc(sizeof(maze_t));
    maze->num_rooms = 2;
    maze->rooms = malloc(sizeof(room_t) * 2);
    maze->rooms[0].name = strdup("room1");
    maze->rooms[1].name = strdup("room2");

    maze->matrix = malloc(sizeof(int *) * 2);
    maze->matrix[0] = malloc(sizeof(int) * 2);
    maze->matrix[1] = malloc(sizeof(int) * 2);

    free_maze(maze);
}
