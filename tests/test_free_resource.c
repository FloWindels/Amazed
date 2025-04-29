/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_free_resource.c
*/

#include <criterion/criterion.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "algorithm.h"
#include "amazed.h"
#include "path_types.h"

Test(free_opt_resources, frees_all_robot_paths)
{
    opt_resources_t *res = malloc(sizeof(opt_resources_t));
    res->robot_paths = malloc(sizeof(path_option_t *) * 2);
    res->path_counts = malloc(sizeof(int) * 2);
    res->path_usage = malloc(sizeof(int) * 2);
    res->path_counts[0] = 2;
    res->path_counts[1] = 1;

    res->robot_paths[0] = malloc(sizeof(path_option_t) * 2);
    res->robot_paths[0][0].path = malloc(sizeof(int) * 3);
    res->robot_paths[0][1].path = malloc(sizeof(int) * 2);

    res->robot_paths[1] = malloc(sizeof(path_option_t) * 1);
    res->robot_paths[1][0].path = malloc(sizeof(int) * 4);

    free_opt_resources(res, 2);
    free(res);
}

Test(free_bool_array, frees_matrix_of_bool)
{
    int size = 2;
    bool **array = malloc(sizeof(bool *) * size);
    for (int i = 0; i < size; i++)
        array[i] = malloc(sizeof(bool) * size);

    free_bool_array(array, size);
}
