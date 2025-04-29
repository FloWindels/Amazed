/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** parser.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "parser.h"
#include "amazed.h"
#include "my.h"

static void insert_room_at_end(info_laby_t *laby, info_room_t *new_room)
{
    info_room_t *current = NULL;

    if (!laby->rooms) {
        laby->rooms = new_room;
    } else {
        current = laby->rooms;
        while (current->next)
            current = current->next;
        current->next = new_room;
    }
}

static void insert_link_at_end(info_laby_t *laby, link_info_t *new_link)
{
    link_info_t *current = NULL;

    if (!laby->links) {
        laby->links = new_link;
    } else {
        current = laby->links;
        while (current->next)
            current = current->next;
        current->next = new_link;
    }
}

static void handle_special_room(info_laby_t *laby, char *name)
{
    if (laby->next_is_start) {
        if (laby->name_room_start)
            free(laby->name_room_start);
        laby->name_room_start = my_strdup(name);
        laby->has_start = true;
        laby->next_is_start = false;
    }
    if (laby->next_is_end) {
        if (laby->name_room_end)
            free(laby->name_room_end);
        laby->name_room_end = my_strdup(name);
        laby->has_end = true;
        laby->next_is_end = false;
    }
}

static int allocate_new_link(link_info_t *new_link, char *room1, char *room2)
{
    new_link->act_room = my_strdup(room1);
    new_link->link_room = my_strdup(room2);
    if (!new_link->act_room || !new_link->link_room) {
        if (new_link->act_room)
            free(new_link->act_room);
        if (new_link->link_room)
            free(new_link->link_room);
        free(new_link);
        return FAILURE;
    }
    new_link->next = NULL;
    return SUCCESS;
}

bool room_exists(info_laby_t *laby, char *name)
{
    info_room_t *current = laby->rooms;

    if (!name)
        return false;
    while (current != NULL) {
        if (my_strlen(current->name_room) != my_strlen(name)) {
            current = current->next;
            continue;
        }
        if (my_strcmp(current->name_room, name) == 0)
            return true;
        current = current->next;
    }
    return false;
}

void init_parsing(info_laby_t *laby)
{
    if (!laby)
        return;
    laby->nb_robots = 0;
    laby->name_room_start = NULL;
    laby->name_room_end = NULL;
    laby->line_start = -1;
    laby->line_end = -1;
    laby->rooms = NULL;
    laby->links = NULL;
    laby->has_start = false;
    laby->has_end = false;
    laby->next_is_start = false;
    laby->next_is_end = false;
}

int insert_data_room(info_laby_t *laby, char *name, int pos_x, int pos_y)
{
    info_room_t *new_room = NULL;

    if (!laby || !name)
        return FAILURE;
    if (room_exists(laby, name))
        return FAILURE;
    new_room = malloc(sizeof(info_room_t));
    if (!new_room)
        return FAILURE;
    new_room->name_room = my_strdup(name);
    if (!new_room->name_room) {
        free(new_room);
        return FAILURE;
    }
    new_room->pos_x = pos_x;
    new_room->pos_y = pos_y;
    new_room->next = NULL;
    handle_special_room(laby, name);
    insert_room_at_end(laby, new_room);
    return SUCCESS;
}

int insert_link_room(info_laby_t *laby, char *room1, char *room2)
{
    link_info_t *new_link = NULL;

    if (!laby || !room1 || !room2)
        return FAILURE;
    if (!room_exists(laby, room1) || !room_exists(laby, room2))
        return FAILURE;
    new_link = malloc(sizeof(link_info_t));
    if (!new_link)
        return FAILURE;
    if (allocate_new_link(new_link, room1, room2) == FAILURE)
        return FAILURE;
    insert_link_at_end(laby, new_link);
    return SUCCESS;
}
