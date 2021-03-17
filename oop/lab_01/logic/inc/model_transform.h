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
    matrix_t dimensional_coords = 
    {
        .matrix = NULL,
        .n = 0,
        .m = 0,
    };
    matrix_t connection = 
    {
        .matrix = NULL,
        .n = 0,
        .m = 0,
    }; //Индексы соединенных ребрами вершин
} math_model_t;

void move(math_model_t &figure, changes_params_t &params);

error_code rotate(math_model_t &figure, changes_params_t &params);

error_code scale(math_model_t &figure, changes_params_t &params);
#endif