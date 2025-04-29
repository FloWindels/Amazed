/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_simulation.c
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include "amazed.h"
#include "algorithm.h"

int optimize_robot_paths(simulation_t *sim, maze_t *maze);

char **perform_simulation_step(simulation_t *sim, maze_t *maze, int *move_count);

Test(init_simulation, initializes_all_fields)
{
    maze_t maze = {.num_rooms = 2, .start_idx = 0, .end_idx = 1};
    simulation_t *sim = init_simulation(&maze, 1);

    cr_assert_not_null(sim);
    cr_assert_eq(sim->robots[0].current_room, 0);
    cr_assert_eq(sim->room_occupancy[0], -2);
    cr_assert_eq(sim->room_occupancy[1], -2);

    free(sim->robots);
    free(sim->room_occupancy);
    free(sim);
}
