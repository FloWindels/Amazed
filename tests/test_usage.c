/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** test_usage.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my.h"

void display_usage(void);

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(display_usage, prints_correct_usage_text, .init = redirect_all_std)
{
    display_usage();
    cr_assert_stdout_ends_with("the robots in a maze from the entrance to the exit\n");
}
