/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** formatter.c
*/

#include "my.h"

static void print_move_per_step(char ***all_moves, int i,
    int *moves_per_step)
{
    for (int j = 1; j < moves_per_step[i]; j++) {
        my_putstr(" ");
        my_putstr(all_moves[i][j]);
    }
}

void print_robot_moves(char ***all_moves, int num_steps,
    int *moves_per_step)
{
    my_putstr("#moves\n");
    for (int i = 0; i < num_steps; i++) {
        if (all_moves[i] && moves_per_step[i] > 0) {
            my_putstr(all_moves[i][0]);
            print_move_per_step(all_moves, i, moves_per_step);
            my_putstr("\n");
        }
    }
}

void print_room(char *name, int pos_x, int pos_y)
{
    my_putstr(name);
    my_putstr(" ");
    my_put_nbr(pos_x);
    my_putstr(" ");
    my_put_nbr(pos_y);
    my_putstr("\n");
}
