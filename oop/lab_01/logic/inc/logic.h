#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <fstream>
#include <cmath>

#define DIMENSION 3

enum action_number
{
    get_model,
    save_model,
    move_action,
    rotate_action,
    scale_action,
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
} error_code;

typedef struct
{
    double move[DIMENSION] = {0};
    double angle[DIMENSION] = {0};
    double k[DIMENSION] = {0};
    double center[DIMENSION] = {0};
} changes_params_t;


typedef struct 
{
    double **matrix;
    int n;
    int m;
} matrix_t;

typedef struct
{
    int points_amount = 0;
    int connections_amount = 0;
    matrix_t dimensional_coords;
    matrix_t connection; //Индексы соединенных ребрами вершин
} math_model_t;


error_code make_action(math_model_t &figure, changes_params_t &params, int action);

#endif