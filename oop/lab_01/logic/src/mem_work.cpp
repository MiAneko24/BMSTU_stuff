#include "../inc/mem_work.h"

void null_matrix(matrix_t &matrix)
{
    for (int i = 0; i < matrix.n; i++)
        for (int j = 0; j < matrix.m; j++)
            matrix.matrix[i][j] = 0;
}

error_code allocate_matrix(matrix_t &mat)
{
    mat.matrix = (double **) malloc(sizeof(double *) * mat.n + sizeof(double) * mat.n * mat.m);
    if (mat.matrix == NULL)
        return error_memory;

    for (int i = 0; i < mat.n; i++)
        mat.matrix[i] = (double *)((char *) mat.matrix + mat.n * sizeof(double *) + (i * mat.m) * sizeof(double));

    null_matrix(mat);

    return no_errors;
}

error_code allocate_point_t(point_t &point)
{
    error_code result = no_errors;

    point.n = MAT_SIZE;
    point.coords = (double *) calloc(point.n, sizeof(double));
    
    if (point.coords == NULL)
        result = error_memory;
    
    return result;
}

error_code allocate_points_array_t(points_array_t &points)
{
    error_code result = no_errors;

    points.array = (point_t *) calloc(points.amount, sizeof(point_t));
    if (points.array == NULL)
        return error_memory;


    for (int i = 0; i < points.amount && !result; i++)
        result = allocate_point_t(points.array[i]); 
    
    return result;
}

void free_matrix(matrix_t &mat)
{
    if (mat.matrix)
        free(mat.matrix);
    
    mat.n = 0;
    mat.m = 0;
    mat.matrix = NULL;
}

void free_point_t(point_t &point)
{
    if (point.coords)
        free(point.coords);
}

void free_points_t(points_array_t &points)
{
    if (points.array)
        for (int i = 0; i < points.amount; i++)
            free_point_t(points.array[i]);
}

void free_math_model_t(math_model_t &figure)
{
    free_points_t(figure.points);   
    free_matrix(figure.connection);
}

void matrix_t_init(matrix_t &mat, int n, int m)
{
    mat.n = n;
    mat.m = m;
    mat.matrix = NULL;
}

point_t point_t_init()
{
    point_t point;
    point.n = MAT_SIZE;
    point.coords = nullptr;
    return point;
}

points_array_t points_t_init()
{
    points_array_t points;
    points.array = nullptr;
    points.amount = 0;
    return points;
}

math_model_t math_model_t_init()
{
    math_model_t figure;
    figure.points = points_t_init();
    matrix_t_init(figure.connection, 0, 0);
    return figure;
}
