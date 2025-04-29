/*
** EPITECH PROJECT, 2025
** clean_str
** File description:
** rm all char from the str
*/

#include "my.h"

char *clean_str(char *src, char *rm_char)
{
    for (int i = 0; rm_char[i]; i++)
        src = rm_char_form_str(src, rm_char[i]);
    return src;
}
