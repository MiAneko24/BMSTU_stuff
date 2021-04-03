#include "../inc/mem_work.h"

void null_matrix(matrix_t &matrix)
{
    for (int i = 0; i < matrix.n; i++)
    {
        for (int j = 0; j < matrix.m; j++)
            matrix.matrix[i][j] = 0;
    }
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

error_code create_point_t(point_t &point)
{
    error_code result = no_errors;
    point.n = MAT_SIZE;
    point.coords = (double *) calloc(point.n, sizeof(double));
    if (point.coords == NULL)
        result = error_memory;
    return result;
}

error_code create_points_array_t(points_array_t &points)
{
    error_code result = no_errors;
    points.array = (point_t *) calloc(points.amount, sizeof(point_t));
    if (points.array == NULL)
        return error_memory;
    for (int i = 0; i < points.amount && !result; i++)
    {
        result = create_point_t(points.array[i]); 
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
    if (figure.points.array)
    {
        for (int i = 0; i < figure.points.amount; i++)
        {
            if (figure.points.array[i].coords)
                free(figure.points.array[i].coords);
        }
    }
    if (figure.connection.matrix)
    {
        free(figure.connection.matrix);
        figure.connection.n = 0;
        figure.connection.matrix = NULL;
    }
}

void math_model_t_init(math_model_t &figure)
{
    if (!figure.inited)
    {
        figure.points.array = NULL;
        figure.points.amount = 0;
        figure.connection.matrix = NULL;
        figure.connection.n = 0;
        figure.connection.m = 0;
        figure.inited = true;
    }
}
