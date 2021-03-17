#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <QPainter>
#define DIMENSION 3


enum action_number
{
    get_model,
    save_model,
    move_action,
    rotate_action,
    scale_action,
    draw_action,
    free_memory,
};

typedef enum
{
    no_errors,
    error_input, 
    error_file,
    error_file_input,
    error_memory,
    error_void,
    error_input_filename,
} error_code;

typedef struct
{
    double center[DIMENSION] = {0};
    double changes[DIMENSION] = {0};
    char *filename = NULL;
    int action;
    QPainter *painter = NULL;
} changes_params_t;


error_code make_action(changes_params_t &params);

#endif