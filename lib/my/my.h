/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** header file for my lib
*/

#ifndef MY_H_
    #define MY_H_

int my_strcmp(char const *s1, char const *s2);
int my_strlen(char const *str);
int my_putstr(char const *str);
char *my_strdup(char const *str);
void free_word_array(char **array);
const char *long_to_string(char *buffer, long int num, int lead_zero);
int my_str_isnum(char const *str);
char *clean_str(char *src, char *rm_char);
char *rm_char_form_str(char *src, char rm);
int my_getnbr(char const *str);
char **my_strtok(char *str, char *delimiters);
int my_arrlen(char **arr);
int my_put_nbr(int nb);
void my_putchar(char c);
char *my_strchr(const char *str, int c);

#endif
