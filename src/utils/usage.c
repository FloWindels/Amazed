/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** usage.c
*/

#include "my.h"
#include <unistd.h>

void display_usage(void)
{
    my_putstr("USAGE:\n\t./amazed [-h]\n");
    my_putstr("\nDESCRIPTION:\n");
    my_putstr("\tAmazed\tis project who make move all ");
    my_putstr("the robots in a maze from the entrance to the exit\n");
}
