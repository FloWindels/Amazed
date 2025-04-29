/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** validation.c - Functions to validate the labyrinth structure
*/

#include <stdlib.h>
#include <stdbool.h>

#include "my.h"
#include "parser.h"
#include "amazed.h"

static bool validate_room(info_room_t *rooms, info_room_t *current)
{
    info_room_t *check = rooms;

    while (check != NULL) {
        if (check != current &&
                check->pos_x == current->pos_x &&
                check->pos_y == current->pos_y) {
            return false;
        }
        check = check->next;
    }
    return true;
}

static bool check_unique_start_end(info_laby_t *laby)
{
    info_room_t *current = laby->rooms;
    int start_count = 0;
    int end_count = 0;

    while (current != NULL) {
        if (my_strcmp(current->name_room, laby->name_room_start) == 0 &&
                my_strlen(current->name_room) ==
                my_strlen(laby->name_room_start))
            start_count++;
        if (my_strcmp(current->name_room, laby->name_room_end) == 0 &&
                my_strlen(current->name_room) ==
                my_strlen(laby->name_room_end))
            end_count++;
        current = current->next;
    }
    return (start_count == 1 && end_count == 1);
}

bool validate_room_coordinates(info_laby_t *laby)
{
    info_room_t *current = laby->rooms;

    if (!current)
        return false;
    while (current != NULL) {
        if (!validate_room(laby->rooms, current))
            return false;
        current = current->next;
    }
    return true;
}

bool start_end_valid(info_laby_t *laby)
{
    if (!laby->has_start || !laby->has_end)
        return false;
    if (!room_exists(laby, laby->name_room_start) ||
        !room_exists(laby, laby->name_room_end))
        return false;
    if (my_strcmp(laby->name_room_start, laby->name_room_end) == 0)
        return false;
    if (!check_unique_start_end(laby))
        return false;
    return true;
}

bool validate_all_links(info_laby_t *laby)
{
    link_info_t *current = laby->links;
    bool start_connected = false;
    bool end_connected = false;

    if (!current)
        return false;
    while (current != NULL) {
        if (!room_exists(laby, current->act_room) ||
            !room_exists(laby, current->link_room))
            return false;
        if (my_strcmp(current->act_room, laby->name_room_start) == 0 ||
            my_strcmp(current->link_room, laby->name_room_start) == 0)
            start_connected = true;
        if (my_strcmp(current->act_room, laby->name_room_end) == 0 ||
            my_strcmp(current->link_room, laby->name_room_end) == 0)
            end_connected = true;
        current = current->next;
    }
    return start_connected && end_connected;
}

int validate_labyrinth(info_laby_t *laby)
{
    if (!laby->rooms)
        return FAILURE;
    if (laby->nb_robots <= 0)
        return FAILURE;
    if (!start_end_valid(laby))
        return FAILURE;
    if (!validate_room_coordinates(laby))
        return FAILURE;
    if (!validate_all_links(laby))
        return FAILURE;
    return SUCCESS;
}
