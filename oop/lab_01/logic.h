#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <fstream>
#include <cmath>

#define MAT_SIZE 4
#define DIMENSION 3

#define CAMERA_Z 10

typedef enum
{
    no_errors,
    error_input, 
    error_file,
    error_file_input,
    error_memory,
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
    int amount;
    matrix_t up_coords; //Заменить верхние и нижние координаты на единое целое
    matrix_t down_coords;
    matrix_t prospect_coords;
    matrix_t connection; //Индексы соединенных ребрами вершин
} math_model_t;


#endif