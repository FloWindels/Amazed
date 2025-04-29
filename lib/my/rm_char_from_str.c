/*
** EPITECH PROJECT, 2025
** rm_char_from_str
** File description:
** remove all same char in a string
*/

char *move_str(char *src, int i)
{
    int j = 0;

    for (j = i; src[j + 1]; j++)
        src[j] = src[j + 1];
    src[j] = '\0';
    return src;
}

char *rm_char_form_str(char *src, char rm)
{
    for (int i = 0; src[i]; i++) {
        if (src[i] == rm) {
            src = move_str(src, i);
        }
    }
    return src;
}
