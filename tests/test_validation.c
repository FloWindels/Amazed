/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_validation.c
*/

/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_validation.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "parser.h"
#include "amazed.h"
#include "my.h"

bool room_exists(info_laby_t *laby, char *name);

Test(validate_room_coordinates, valid_unique_coordinates)
{
    info_laby_t laby = {0};
    info_room_t room1 = {.name_room = "A", .pos_x = 1, .pos_y = 1, .next = NULL};
    info_room_t room2 = {.name_room = "B", .pos_x = 2, .pos_y = 2, .next = NULL};
    room1.next = &room2;
    laby.rooms = &room1;

    cr_assert_eq(validate_room_coordinates(&laby), true);
}

Test(validate_room_coordinates, invalid_duplicate_coordinates)
{
    info_laby_t laby = {0};
    info_room_t room1 = {.name_room = "A", .pos_x = 1, .pos_y = 1, .next = NULL};
    info_room_t room2 = {.name_room = "B", .pos_x = 1, .pos_y = 1, .next = NULL};
    room1.next = &room2;
    laby.rooms = &room1;

    cr_assert_eq(validate_room_coordinates(&laby), false);
}

Test(start_end_valid, valid_case)
{
    info_laby_t laby = {
        .nb_robots = 1,
        .has_start = true,
        .has_end = true,
        .name_room_start = "Start",
        .name_room_end = "End"
    };
    info_room_t room1 = {.name_room = "Start", .pos_x = 0, .pos_y = 0};
    info_room_t room2 = {.name_room = "End", .pos_x = 1, .pos_y = 1};
    room1.next = &room2;
    laby.rooms = &room1;

    cr_assert_eq(start_end_valid(&laby), true);
}

Test(start_end_valid, same_start_and_end_name)
{
    info_laby_t laby = {
        .nb_robots = 1,
        .has_start = true,
        .has_end = true,
        .name_room_start = "Room",
        .name_room_end = "Room"
    };
    info_room_t room = {.name_room = "Room", .pos_x = 0, .pos_y = 0};
    laby.rooms = &room;

    cr_assert_eq(start_end_valid(&laby), false);
}

Test(validate_all_links, valid_links_connected_to_start_and_end)
{
    info_laby_t laby = {
        .name_room_start = "Start",
        .name_room_end = "End"
    };
    info_room_t room1 = {.name_room = "Start", .next = NULL};
    info_room_t room2 = {.name_room = "End", .next = NULL};
    room1.next = &room2;
    laby.rooms = &room1;

    link_info_t link1 = {.act_room = "Start", .link_room = "Mid"};
    link_info_t link2 = {.act_room = "Mid", .link_room = "End"};
    link1.next = &link2;
    laby.links = &link1;

    cr_assert_eq(validate_all_links(&laby), true);
}

Test(validate_labyrinth, fully_valid_labyrinth)
{
    info_laby_t laby = {
        .nb_robots = 2,
        .has_start = true,
        .has_end = true,
        .name_room_start = "Start",
        .name_room_end = "End"
    };
    info_room_t room1 = {.name_room = "Start", .pos_x = 0, .pos_y = 0};
    info_room_t room2 = {.name_room = "End", .pos_x = 1, .pos_y = 1};
    room1.next = &room2;
    laby.rooms = &room1;

    link_info_t link1 = {.act_room = "Start", .link_room = "End"};
    laby.links = &link1;

    cr_assert_eq(validate_labyrinth(&laby), SUCCESS);
}
