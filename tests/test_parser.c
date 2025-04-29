/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_parser.c
*/

#include <criterion/criterion.h>
#include "parser.h"
#include "my.h"

Test(parser, init_parsing_should_set_default_values)
{
    info_laby_t laby;
    init_parsing(&laby);

    cr_assert_eq(laby.nb_robots, 0);
    cr_assert_null(laby.name_room_start);
    cr_assert_null(laby.name_room_end);
    cr_assert_eq(laby.line_start, -1);
    cr_assert_eq(laby.line_end, -1);
    cr_assert_null(laby.rooms);
    cr_assert_null(laby.links);
    cr_assert_not(laby.has_start);
    cr_assert_not(laby.has_end);
    cr_assert_not(laby.next_is_start);
    cr_assert_not(laby.next_is_end);
}

Test(parser, insert_data_room_should_add_room)
{
    info_laby_t laby;
    init_parsing(&laby);

    int result = insert_data_room(&laby, "room1", 10, 20);

    cr_assert_eq(result, 0);
    cr_assert_not_null(laby.rooms);
    cr_assert_str_eq(laby.rooms->name_room, "room1");
    cr_assert_eq(laby.rooms->pos_x, 10);
    cr_assert_eq(laby.rooms->pos_y, 20);
    free_labyrinth(&laby);
}

Test(parser, room_exists_should_find_existing_room)
{
    info_laby_t laby;
    init_parsing(&laby);
    insert_data_room(&laby, "room2", 5, 5);

    cr_assert(room_exists(&laby, "room2"));
    cr_assert_not(room_exists(&laby, "not_found"));
    free_labyrinth(&laby);
}

Test(parser, insert_link_room_should_add_link)
{
    info_laby_t laby;
    init_parsing(&laby);
    insert_data_room(&laby, "A", 0, 0);
    insert_data_room(&laby, "B", 1, 1);

    int result = insert_link_room(&laby, "A", "B");

    cr_assert_eq(result, 0);
    cr_assert_not_null(laby.links);
    cr_assert_str_eq(laby.links->act_room, "A");
    cr_assert_str_eq(laby.links->link_room, "B");
    free_labyrinth(&laby);
}
