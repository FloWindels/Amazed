/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** main.c - Entry point for the amazed program
*/

#include <unistd.h>

#include "amazed.h"
#include "output.h"
#include "parser.h"
#include "my.h"

int main(int argc, char const *argv[])
{
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0) {
        display_usage();
        return SUCCESS;
    }
    if (argc != 1)
        return FAILURE;
    if (parse_and_validate() != SUCCESS) {
        write(2, "Error\n", 6);
        return FAILURE;
    }
    return SUCCESS;
}
