#ifndef MEM_WORK_H
#define MEM_WORK_H
#include "logic.h"
#include "model_transform.h"

void null_matrix(matrix_t &matrix);


error_code create_matrix(matrix_t &mat);

void free_matrix(matrix_t &mat);

void copy_math_model_t(math_model_t &to, math_model_t &from);

void free_math_model_t(math_model_t &figure);


#endif