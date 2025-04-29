/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_parser.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "amazed.h"
#include "parser.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(parse_and_validate, invalid_robot_number_should_fail, .init = redirect_all_std)
{
    const char *input = "notanumber\n";

    FILE *fp = fmemopen((void *)input, strlen(input), "r");
    cr_assert_not_null(fp);

    FILE *original_stdin = stdin;
    stdin = fp;

    int result = parse_and_validate();

    cr_assert_eq(result, FAILURE, "Expected parse_and_validate to fail");

    stdin = original_stdin;
    fclose(fp);
}

Test(parse_and_validate, room_with_missing_coordinates_should_fail, .init = redirect_all_std)
{
    const char *input =
        "3\n"
        "room1 0\n";

    FILE *fp = fmemopen((void *)input, strlen(input), "r");
    cr_assert_not_null(fp);

    FILE *original_stdin = stdin;
    stdin = fp;

    int result = parse_and_validate();

    cr_assert_eq(result, FAILURE, "Expected parse_and_validate to fail on malformed room");

    stdin = original_stdin;
    fclose(fp);
}
