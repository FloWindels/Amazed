/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-amazed-nathan.cheynet
** File description:
** Improved robot movement logic that handles traffic and alternative paths
*/

#include <stdlib.h>
#include <stdbool.h>

#include "amazed.h"
#include "my.h"
#include "algorithm.h"

static bool robot_is_at_end(robot_t *robot, maze_t *maze)
{
    if (robot->reached_end)
        return true;
    if (robot->current_room == maze->end_idx) {
        robot->reached_end = true;
        return true;
    }
    if (robot->path_position >= robot->path_length - 1) {
        robot->reached_end = true;
        return true;
    }
    return false;
}

static bool execute_robot_move(simulation_t *sim, maze_t *maze, robot_t *robot,
    int next_room)
{
    int old_room = robot->current_room;

    if (old_room != maze->start_idx && old_room != maze->end_idx)
        sim->room_occupancy[old_room] = -1;
    if (next_room != maze->start_idx && next_room != maze->end_idx)
        sim->room_occupancy[next_room] = robot->robot_id;
    robot->current_room = next_room;
    robot->path_position++;
    if (next_room == maze->end_idx)
        robot->reached_end = true;
    return true;
}

char *create_move_string(robot_t *robot, char *room_name)
{
    char id_buffer[32];
    const char *id_str = long_to_string(id_buffer, robot->robot_id, 0);
    int id_len = my_strlen(id_str);
    int name_len = my_strlen(room_name);
    int total_len = id_len + name_len + 2;
    char *move_str = malloc(sizeof(char) * (total_len + 1));

    if (!move_str)
        return NULL;
    move_str[0] = 'P';
    for (int i = 0; i < id_len; i++)
        move_str[1 + i] = id_str[i];
    move_str[1 + id_len] = '-';
    for (int i = 0; i < name_len; i++)
        move_str[id_len + 2 + i] = room_name[i];
    move_str[total_len] = '\0';
    return move_str;
}

bool try_move_robot(simulation_t *sim, maze_t *maze, int robot_idx)
{
    robot_t *robot = &sim->robots[robot_idx];
    int next_room = 0;
    int alt_room = 0;

    if (robot_is_at_end(robot, maze))
        return false;
    if (!robot->path || robot->path_position + 1 >= robot->path_length)
        return false;
    next_room = robot->path[robot->path_position + 1];
    if (next_room < 0 || next_room >= maze->num_rooms)
        return false;
    if (next_room == maze->end_idx || sim->room_occupancy[next_room] == -1)
        return execute_robot_move(sim, maze, robot, next_room);
    alt_room = find_alternative_route(sim, maze, robot_idx);
    if (alt_room != -1)
        return execute_robot_move(sim, maze, robot, alt_room);
    return false;
}

bool add_robot_move(move_data_t *data)
{
    robot_t *robot = &data->sim->robots[data->robot_idx];
    int room_idx = robot->current_room;
    char *room_name = data->maze->rooms[room_idx].name;
    char *move_str = create_move_string(robot, room_name);

    if (!move_str)
        return false;
    data->step_moves[(*data->move_count)] = move_str;
    (*data->move_count) += 1;
    return true;
}

static char **init_step_move_data(move_data_t *move_data, simulation_t *sim,
    maze_t *maze, int *move_count)
{
    char **step_moves = malloc(sizeof(char *) * sim->num_robots);

    if (!step_moves)
        return NULL;
    move_data->sim = sim;
    move_data->maze = maze;
    move_data->step_moves = step_moves;
    move_data->move_count = move_count;
    *move_count = 0;
    for (int i = 0; i < sim->num_robots; i++)
        step_moves[i] = NULL;
    return step_moves;
}

char **perform_simulation_step(simulation_t *sim, maze_t *maze,
    int *move_count)
{
    move_data_t move_data;
    char **step_moves = init_step_move_data(&move_data, sim, maze, move_count);

    if (!step_moves)
        return NULL;
    for (int i = 0; i < sim->num_robots; i++) {
        move_data.robot_idx = i;
        if (try_move_robot(sim, maze, i) && !add_robot_move(&move_data)) {
            free_word_array(step_moves);
            return NULL;
        }
    }
    if (*move_count == 0) {
        free(step_moves);
        return NULL;
    }
    return step_moves;
}
