/*
** EPITECH PROJECT, 2024
** my_str_isnum
** File description:
** Return if string contains only num char
*/

#include "my.h"
#include <stdio.h>

int my_str_isnum(char const *str)
{
    int i = 0;

    if (my_strlen(str) == 0)
        return 0;
    if (str[0] == '-')
        i = 1;
    if (i == 1 && str[i] == '\0')
        return 0;
    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}
