/*
** EPITECH PROJECT, 2024
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** amazed.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "amazed.h"
#include "parser.h"
#include "output.h"
#include "my.h"

static int process_num_robots(info_laby_t *laby, char *line)
{
    if (!my_str_isnum(line))
        return FAILURE;
    laby->nb_robots = my_getnbr(line);
    if (laby->nb_robots <= 0)
        return FAILURE;
    my_putstr("#number_of_robots\n");
    my_put_nbr(laby->nb_robots);
    my_putchar('\n');
    return SUCCESS;
}

static int process_room_line(info_laby_t *laby, char *line)
{
    char **data = my_strtok(line, " ");
    int x_y[2];

    if (!data || my_arrlen(data) < 3) {
        free_word_array(data);
        return FAILURE;
    }
    if (!my_str_isnum(data[1]) || !my_str_isnum(data[2])) {
        free_word_array(data);
        return FAILURE;
    }
    x_y[0] = my_getnbr(data[1]);
    x_y[1] = my_getnbr(data[2]);
    if (insert_data_room(laby, data[0], x_y[0], x_y[1]) != SUCCESS) {
        free_word_array(data);
        return FAILURE;
    }
    print_room(data[0], x_y[0], x_y[1]);
    free_word_array(data);
    return SUCCESS;
}

static int process_command_line(info_laby_t *laby, char *line)
{
    if (my_strcmp(line, "##start") == 0) {
        laby->next_is_start = true;
        my_putstr("##start\n");
        return SUCCESS;
    } else if (my_strcmp(line, "##end") == 0) {
        laby->next_is_end = true;
        my_putstr("##end\n");
        return SUCCESS;
    }
    return SUCCESS;
}

static int process_link_line(info_laby_t *laby, char *line)
{
    char **data = my_strtok(line, "-");

    if (!data || my_arrlen(data) != 2) {
        free_word_array(data);
        return FAILURE;
    }
    if (insert_link_room(laby, data[0], data[1]) != SUCCESS) {
        free_word_array(data);
        return FAILURE;
    }
    my_putstr(data[0]);
    my_putchar('-');
    my_putstr(data[1]);
    my_putchar('\n');
    free_word_array(data);
    return SUCCESS;
}

static int skip_initial_comments(char **line, size_t *len)
{
    ssize_t read;

    do {
        read = getline(line, len, stdin);
        if (read == -1)
            return FAILURE;
        if ((*line)[read - 1] == '\n')
            (*line)[read - 1] = '\0';
    } while ((*line)[0] == '#' && (*line)[1] != '#');
    return SUCCESS;
}

static int initialize_labyrinth(info_laby_t *laby, char **line, size_t *len)
{
    init_parsing(laby);
    if (skip_initial_comments(line, len) != SUCCESS) {
        free(*line);
        return FAILURE;
    }
    if (process_num_robots(laby, *line) != SUCCESS) {
        free(*line);
        return FAILURE;
    }
    my_putstr("#rooms\n");
    return SUCCESS;
}

static int process_line(info_laby_t *laby, char *line, bool *started_links)
{
    if (line[0] == '\0' || (line[0] == '#' && line[1] != '#'))
        return SUCCESS;
    if (line[0] == '#' && line[1] == '#') {
        return process_command_line(laby, line);
    }
    if (my_strchr(line, '-') && !my_strchr(line, ' ')) {
        if (!(*started_links)) {
            my_putstr("#tunnels\n");
            *started_links = true;
        }
        return process_link_line(laby, line);
    } else {
        return process_room_line(laby, line);
    }
}

static int parse_input_file(info_laby_t *laby)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    bool started_links = false;

    if (initialize_labyrinth(laby, &line, &len) != SUCCESS)
        return FAILURE;
    read = getline(&line, &len, stdin);
    while (read != -1) {
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';
        if (process_line(laby, line, &started_links) != SUCCESS) {
            free(line);
            return FAILURE;
        }
        read = getline(&line, &len, stdin);
    }
    free(line);
    return SUCCESS;
}

int parse_and_validate(void)
{
    info_laby_t laby;

    if (parse_input_file(&laby) != SUCCESS)
        return FAILURE;
    if (validate_labyrinth(&laby) != SUCCESS) {
        free_labyrinth(&laby);
        return FAILURE;
    }
    if (solve_and_print_maze(&laby) != SUCCESS) {
        free_labyrinth(&laby);
        return FAILURE;
    }
    free_labyrinth(&laby);
    return SUCCESS;
}
