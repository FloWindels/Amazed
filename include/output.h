/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** output.h
*/

#ifndef OUTPUT_H_
    #define OUTPUT_H_

void display_usage(void);
void print_robot_moves(char ***all_moves, int num_steps,
    int *moves_per_step);
void print_room(char *name, int pos_x, int pos_y);

#endif
