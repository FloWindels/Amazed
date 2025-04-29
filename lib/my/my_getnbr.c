/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** retrieve a number in a string
*/

#include <stdio.h>

static int my_find_sign(char const *str)
{
    int count_minus = 0;
    int index = 0;

    while (str[index] != '\0' && (str[index] < '0' || str[index] > '9')) {
        if (str[index] == '-')
            count_minus += 1;
        index += 1;
    }
    if (count_minus % 2 != 0)
        return -1;
    return 1;
}

int my_getnbr(char const *str)
{
    long nb = 0;
    int index = 0;
    int sign = my_find_sign(str);
    int max = 2147483647;
    int min = -2147483648;

    while (str[index] != '\0' && (str[index] < '0' || str[index] > '9'))
        index += 1;
    if (str[index] == '\0')
        return 0;
    while (str[index] >= '0' && str[index] <= '9') {
        nb = nb * 10 + (str[index] - '0');
        if (nb * sign > max || nb * sign < min)
            return 0;
        index += 1;
    }
    return (int)(nb * sign);
}
