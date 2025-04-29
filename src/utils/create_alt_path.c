/*
** EPITECH PROJECT, 2024
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** create_alt_path.c
*/

#include <stdlib.h>

#include "amazed.h"

static int count_alt_path_length(int alt_room, int end_idx, int *new_pred)
{
    int path_len = 0;
    int temp = end_idx;

    while (temp != alt_room) {
        path_len++;
        temp = new_pred[temp];
        if (temp == -1)
            return -1;
    }
    return path_len + 2;
}

static int *allocate_alt_path(int path_len, int *new_pred)
{
    int *new_path = malloc(sizeof(int) * path_len);

    if (!new_path) {
        free(new_pred);
        return NULL;
    }
    return new_path;
}

static void fill_alt_path(int *new_path, int cur_alt_end_len[4], int *new_pred)
{
    int temp = cur_alt_end_len[2];
    int idx = cur_alt_end_len[3] - 1;

    new_path[0] = cur_alt_end_len[0];
    new_path[1] = cur_alt_end_len[1];
    new_path[idx] = temp;
    idx -= 1;
    while (temp != cur_alt_end_len[1]) {
        temp = new_pred[temp];
        if (temp == -1)
            break;
        new_path[idx] = temp;
        idx -= 1;
    }
}

static int update_robot_path(robot_t *robot, int *new_path, int path_len)
{
    free(robot->path);
    robot->path = new_path;
    robot->path_length = path_len;
    robot->path_position = 0;
    return 0;
}

int create_alt_path(robot_t *robot, maze_t *maze,
    int current_alt_room[2], int *new_pred)
{
    int path_len = count_alt_path_length(current_alt_room[1], maze->end_idx,
        new_pred);
    int *new_path = NULL;

    if (path_len == -1) {
        free(new_pred);
        return -1;
    }
    new_path = allocate_alt_path(path_len, new_pred);
    if (!new_path)
        return -1;
    fill_alt_path(new_path, (int[4]){current_alt_room[0], current_alt_room[1],
        maze->end_idx, path_len}, new_pred);
    update_robot_path(robot, new_path, path_len);
    free(new_pred);
    return current_alt_room[1];
}
