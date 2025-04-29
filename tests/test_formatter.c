/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_formatter.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my.h"

void print_robot_moves(char ***all_moves, int num_steps, int *moves_per_step);
void print_room(char *name, int pos_x, int pos_y);

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(print_robot_moves, prints_correctly_formatted_moves, .init = redirect_all_std)
{
    char ***moves = malloc(sizeof(char **) * 2);

    moves[0] = malloc(sizeof(char *) * 3);
    moves[0][0] = "L1-roomA";
    moves[0][1] = "L2-roomB";
    moves[0][2] = NULL;

    moves[1] = malloc(sizeof(char *) * 2);
    moves[1][0] = "L1-roomC";
    moves[1][1] = NULL;

    int move_counts[2] = {2, 1};

    print_robot_moves(moves, 2, move_counts);

    cr_assert_stdout_eq_str("#moves\nL1-roomA L2-roomB\nL1-roomC\n");

    free(moves[0]);
    free(moves[1]);
    free(moves);
}

Test(print_room, prints_single_room_line, .init = redirect_all_std)
{
    print_room("start", 3, 7);
    cr_assert_stdout_eq_str("start 3 7\n");
}
