#ifndef MEM_WORK_H
#define MEM_WORK_H
#include "logic.h"
#include "model_transform.h"

void null_matrix(matrix_t &matrix);

error_code allocate_matrix(matrix_t &mat);

void free_matrix(matrix_t &mat);

void free_math_model_t(math_model_t &figure);

math_model_t math_model_t_init();

void matrix_t_init(matrix_t &mat, int n, int m);

void free_points_t(points_array_t &points);

error_code allocate_points_array_t(points_array_t &points);

#endif