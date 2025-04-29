/*
** EPITECH PROJECT, 2024
** my_arrlen
** File description:
** return the number row there are on a array
*/

#include <stddef.h>

int my_arrlen(char **arr)
{
    int i = 0;

    while (arr[i] != NULL)
        i++;
    return i;
}
