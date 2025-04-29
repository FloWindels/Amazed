/*
** EPITECH PROJECT, 2024
** my_strtok
** File description:
** Similare to my_str_to_word_array but you can use delimiter
*/

#include "my.h"
#include <stdlib.h>

int separator(char str, char *delimiters)
{
    if (delimiters == NULL)
        return 0;
    for (int i = 0; delimiters[i]; i++) {
        if (str == delimiters[i])
            return 1;
    }
    return 0;
}

int compt_separator(char const *str, char *delimiters)
{
    int compt = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (separator(str[i], delimiters)
            && separator(str[i + 1], delimiters) == 0) {
            compt++;
        }
    }
    if (!separator(str[my_strlen(str)], delimiters))
        compt++;
    return compt;
}

char *word(int z, int mark, const char *str)
{
    char *word;
    int j = 0;

    word = malloc(sizeof(char) * (z - mark + 1));
    if (word == NULL)
        return NULL;
    for (j = 0; j < (z - mark) && (mark + j) < my_strlen(str); j++) {
        word[j] = str[mark + j];
    }
    word[j] = '\0';
    return word;
}

int last_word(int z, char *delimiters, int *mark, char *str)
{
    if (str == NULL || my_strlen(str) <= z)
        return 1;
    if (separator(str[z], delimiters) == 0)
        return 1;
    if (z == *mark) {
        *mark = z + 1;
        return 1;
    }
    return 0;
}

char **my_strtok(char *str, char *delimiters)
{
    int nbw = compt_separator(str, delimiters);
    char **array = malloc(sizeof(char *) * (nbw + 1));
    int mark = 0;
    int i = 0;
    int z = 0;

    for (z = 0; z <= my_strlen(str) + 1; z++) {
        if (last_word(z, delimiters, &mark, str) == 1)
            continue;
        array[i] = word(z, mark, str);
        mark = z + 1;
        i++;
    }
    if (!separator(str[z - 3], delimiters) && z > mark) {
        array[i] = word(z, mark, str);
        i++;
    }
    array[i] = NULL;
    return array;
}
