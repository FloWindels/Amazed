/*
** EPITECH PROJECT, 2024
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** long_to_str.c
*/

const char *my_helper(char **ptr, long int num, int lead_zero)
{
    int neg = (num < 0) ? 1 : 0;

    if (neg)
        num *= -1;
    while (num > 0) {
        *ptr -= 1;
        **ptr = '0' + (num % 10);
        num /= 10;
    }
    if (neg && lead_zero != 1) {
        *ptr -= 1;
        **ptr = '-';
    }
    return *ptr;
}

const char *long_to_string(char *buffer, long int num, int lead_zero)
{
    char *ptr = buffer + 31;

    *ptr = '\0';
    if (num == 0) {
        ptr--;
        *ptr = '0';
        return ptr;
    }
    return my_helper(&ptr, num, lead_zero);
}
