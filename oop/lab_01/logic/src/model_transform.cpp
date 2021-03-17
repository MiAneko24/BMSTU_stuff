#include "../inc/model_transform.h"
#include "../inc/mem_work.h"

void print_mat(matrix_t &mat);
void get_center_coords(changes_params_t &params, math_model_t &figure);
void get_move_matrix_by_center_coords(matrix_t &transform_matrix, changes_params_t &params);

void multiply_matrix(matrix_t &mat_1, matrix_t &mat_2, matrix_t &res)
{
    res.n = mat_1.n;
    res.m = mat_2.m;
    for (int i = 0; i < res.n; i++)
    {
        for (int j = 0; j < res.m; j++)
            for (int k = 0; k < mat_2.n; k++)
            {
                res.matrix[i][j] += mat_1.matrix[i][k] * mat_2.matrix[k][j];
            }
    }
}

error_code get_rotation_transform_matrix_t(matrix_t &transform_matrix, changes_params_t &params)
{
    error_code result = no_errors;
    matrix_t xy =
    {
        .matrix = NULL,
        .n = MAT_SIZE,
        .m = MAT_SIZE,
    };
    matrix_t yz = xy;
    matrix_t xz = xy;
    matrix_t res = xy;
    result = create_matrix(xy);
    if (!result)
    {
        xy.matrix[0][0] = cos(params.changes[0]);
        xy.matrix[0][1] = -sin(params.changes[0]);
        xy.matrix[1][0] = sin(params.changes[0]);
        xy.matrix[1][1] = cos(params.changes[0]);
        xy.matrix[2][2] = 1;
        xy.matrix[DIMENSION][DIMENSION] = 1;
        result = create_matrix(yz);
    }
    if (!result)
    {
        yz.matrix[1][1] = cos(params.changes[1]);
        yz.matrix[1][2] = -sin(params.changes[1]);
        yz.matrix[2][1] = sin(params.changes[1]);
        yz.matrix[2][2] = cos(params.changes[1]);
        yz.matrix[0][0] = 1;
        yz.matrix[DIMENSION][DIMENSION] = 1;
        result = create_matrix(xz);
    }
    if (!result)
    {
        xz.matrix[0][0] = cos(params.changes[2]);
        xz.matrix[0][2] = -sin(params.changes[2]);
        xz.matrix[2][0] = sin(params.changes[2]);
        xz.matrix[2][2] = cos(params.changes[2]);
        xz.matrix[1][1] = 1;
        xz.matrix[DIMENSION][DIMENSION] = 1;
        result = create_matrix(res);
    }
    if (!result)
    {
        multiply_matrix(xy, yz, res);
        multiply_matrix(res, xz, transform_matrix);
        null_matrix(xy);
        for(int i = 0; i < DIMENSION; i++)
            params.center[i] *= -1;
        get_move_matrix_by_center_coords(xy, params);
        null_matrix(res);
        multiply_matrix(xy, transform_matrix, res);
        for(int i = 0; i < DIMENSION; i++)
            params.center[i] *= -1;
        null_matrix(xy);
        get_move_matrix_by_center_coords(xy, params);
        null_matrix(transform_matrix);
        multiply_matrix(res, xy, transform_matrix);
    }
    free_matrix(xy);
    free_matrix(yz);
    free_matrix(xz);
    free_matrix(res);   
    return result;
}

void get_move_matrix_by_center_coords(matrix_t &transform_matrix, changes_params_t &params)
{
    for (int i = 0; i < transform_matrix.n; i++)
        transform_matrix.matrix[i][i] = 1;
    for (int i = 0; i < DIMENSION; i++)
        transform_matrix.matrix[transform_matrix.n - 1][i] = params.center[i];
}

error_code get_scale_transform_matrix_t(matrix_t &transform_matrix, changes_params_t &params)
{
    error_code result = no_errors;
    matrix_t move = {
        .matrix = NULL,
        .n = MAT_SIZE,
        .m = MAT_SIZE,
    };
    matrix_t res = move;
    result = create_matrix(move);
    if (!result)
    {
        result = create_matrix(res);
    }
    if (!result)
    {
        for (int i = 0; i < DIMENSION; i++)
        {
            transform_matrix.matrix[i][i] = params.changes[i];
        }
        for(int i = 0; i < DIMENSION; i++)
            params.center[i] *= -1;
        transform_matrix.matrix[DIMENSION][DIMENSION] = 1;
        get_move_matrix_by_center_coords(move, params);
        multiply_matrix(move, transform_matrix, res);
        null_matrix(transform_matrix);
        for (int i = 0; i < DIMENSION; i++)
        {
            params.center[i] *= -1;
        }
        get_move_matrix_by_center_coords(move,params);
        multiply_matrix(res, move, transform_matrix);
    }
    free_matrix(move);
    free_matrix(res);
    return result;
}



error_code transform_points(matrix_t &mat, int index, matrix_t transform_matrix)
{
    error_code result = no_errors;
    matrix_t prom = 
    {
        .matrix = &mat.matrix[index],
        .n = 1,
        .m = MAT_SIZE,
    };
    matrix_t res = 
    {
        .matrix = NULL,
        .n = prom.n,
        .m = transform_matrix.m,
    };
    result = create_matrix(res);
    if (!result)
    {
        multiply_matrix(prom, transform_matrix, res);
        for (int j = 0; j < MAT_SIZE; j++)
            mat.matrix[index][j] = res.matrix[0][j];
    }
    free_matrix(res);
    free_matrix(prom);
    return result;
}

error_code rotate(math_model_t &figure, changes_params_t &params)
{
    error_code result = no_errors;
    matrix_t transform_matrix =
    {
        .matrix = NULL,
        .n = MAT_SIZE,
        .m = MAT_SIZE,
    };
    result = create_matrix(transform_matrix);
    if (!result)
    {
        get_center_coords(params, figure);
        result = get_rotation_transform_matrix_t(transform_matrix, params);
    }
    for (int i = 0; i < figure.dimensional_coords.n && !result; i++)
    {
        result = transform_points(figure.dimensional_coords, i, transform_matrix);
    }
    free_matrix(transform_matrix);
    return result;
}

void get_center_coords(changes_params_t &params, math_model_t &figure)
{
    for (int i = 0; i < DIMENSION; i++)
        params.center[i] = 0;
    for (int i = 0; i < figure.dimensional_coords.n; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            params.center[j] += figure.dimensional_coords.matrix[i][j];
        }
    }
    for (int j = 0; j < DIMENSION; j++)
        params.center[j] /= figure.dimensional_coords.n;
}

error_code scale(math_model_t &figure, changes_params_t &params)
{
    error_code result = no_errors;
    matrix_t transform_matrix =
    {
        .matrix = NULL,
        .n = MAT_SIZE,
        .m = MAT_SIZE,
    };
    result = create_matrix(transform_matrix);
    if (!result)
    {
        for (int i = 0; i < DIMENSION; i++)
            params.center[i] = 0;
        get_center_coords(params, figure);
        get_scale_transform_matrix_t(transform_matrix, params);
    }
    for (int i = 0; i < figure.dimensional_coords.n && !result; i++)
    {
        result = transform_points(figure.dimensional_coords, i, transform_matrix);
    }
    free_matrix(transform_matrix);
    return result;
}

void move(math_model_t &figure, changes_params_t &params)
{
    for (int i = 0; i < figure.dimensional_coords.n; i++)
    {
        for (int j = 0; j < figure.dimensional_coords.m; j++)
        {
            figure.dimensional_coords.matrix[i][j] += params.changes[j];
        }
    }
}

void copy_matrix(matrix_t &mat_1, matrix_t &mat_2)
{
    for (int i = 0; i < mat_1.n; i++)
        for (int j = 0; j < mat_1.m; j++)
        {
            mat_1.matrix[i][j] = mat_2.matrix[i][j];
        }
}
