#include "../inc/mem_work.h"

void null_matrix(matrix_t &matrix)
{
    for (int i = 0; i < matrix.n; i++)
    {
        for (int j = 0; j < matrix.m; j++)
            matrix.matrix[i][j] = 0;
    }
}

void copy_math_model_t(math_model_t &to, math_model_t &from)
{
    to.connection = from.connection;
    to.dimensional_coords = from.dimensional_coords;
}

error_code create_matrix(matrix_t &mat)
{
    error_code result = no_errors;
    mat.matrix = (double **) malloc(sizeof(double *) * mat.n + sizeof(double) * mat.n * mat.m);
    if (mat.matrix == NULL)
    {
        result = error_memory;
    }
    else
    {
        for (int i = 0; i < mat.n; i++)
        {
            mat.matrix[i] = (double *)((char *) mat.matrix + mat.n * sizeof(double *) + (i * mat.m) * sizeof(double));
        }
        null_matrix(mat);
    }
    return result;
}

void free_matrix(matrix_t &mat)
{
    if (!mat.matrix)
        free(mat.matrix);
    mat.n = 0;
    mat.m = 0;
}


void free_math_model_t(math_model_t &figure)
{
    if (figure.dimensional_coords.matrix)
    {
        free(figure.dimensional_coords.matrix);
        figure.dimensional_coords.matrix = NULL;
        figure.dimensional_coords.n = 0;
    }
    if (figure.connection.matrix)
    {
        free(figure.connection.matrix);
        figure.connection.n = 0;
        figure.connection.matrix = NULL;
    }
}
