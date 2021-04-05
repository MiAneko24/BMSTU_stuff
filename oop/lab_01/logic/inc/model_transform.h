#ifndef MODEL_TRANSFORM_H
#define MODEL_TRANSFORM_H

#define MAT_SIZE 4
#define PAIRS 2
#define LINE 1
#include <iostream>
#include "logic.h"

typedef struct 
{
    double **matrix;
    int n;
    int m;
} matrix_t;

typedef struct 
{
    double *coords;
    int n = MAT_SIZE;
} point_t;

typedef struct
{
    point_t *array;
    int amount;
} points_array_t;

typedef struct
{
    points_array_t points; // Матрица координат точек
    matrix_t connection; //Индексы соединенных ребрами вершин
} math_model_t;

bool model_is_void(math_model_t &figure);

error_code math_model_t_move(math_model_t &figure, changes_params_t &params);

error_code math_model_t_rotate(math_model_t &figure, changes_params_t &params);

error_code math_model_t_scale(math_model_t &figure, changes_params_t &params);
#endif