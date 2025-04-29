/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** parser.h
*/

#include <stdbool.h>

#ifndef PARSER_H_
    #define PARSER_H_

typedef struct link_info_s {
    char *act_room;
    char *link_room;
    struct link_info_s *next;
} link_info_t;

typedef struct info_room_s {
    char *name_room;
    int pos_x;
    int pos_y;
    struct info_room_s *next;
} info_room_t;

typedef struct info_laby_s {
    int nb_robots;
    char *name_room_start;
    int line_start;
    char *name_room_end;
    int line_end;
    info_room_t *rooms;
    link_info_t *links;
    bool has_start;
    bool has_end;
    bool next_is_start;
    bool next_is_end;
} info_laby_t;

void init_parsing(info_laby_t *laby);
int insert_data_room(info_laby_t *laby, char *name, int pos_x, int pos_y);
int insert_link_room(info_laby_t *laby, char *room1, char *room2);
int parse_and_validate(void);

/* Validation */
bool validate_all_links(info_laby_t *laby);
bool validate_room_coordinates(info_laby_t *laby);
bool start_end_valid(info_laby_t *laby);
bool room_exists(info_laby_t *laby, char *name);
int validate_labyrinth(info_laby_t *laby);
int solve_and_print_maze(info_laby_t *laby);

/* Utils functions */
void free_array(char **array);
void free_labyrinth(info_laby_t *laby);
void free_word_array(char **array);

#endif
