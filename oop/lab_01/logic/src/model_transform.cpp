#include "../inc/model_transform.h"
#include "../inc/mem_work.h"

void get_center_coords(changes_params_t &params, points_array_t &points);

void get_move_matrix(matrix_t &transform_matrix, double *changes);


bool model_is_void(points_array_t &points)
{
    if (points.amount == 0)
        return true;
    return false;
}

void multiply_matrix(matrix_t &res, const matrix_t &mat_1, const matrix_t &mat_2)
{
    null_matrix(res);

    for (int i = 0; i < res.n; i++)
        for (int j = 0; j < res.m; j++)
            for (int k = 0; k < mat_2.n; k++)
                res.matrix[i][j] += mat_1.matrix[i][k] * mat_2.matrix[k][j];
}

void copy_matrix(matrix_t &mat_1, const matrix_t &mat_2)
{
    for (int i = 0; i < mat_1.n; i++)
        for (int j = 0; j < mat_1.m; j++)
            mat_1.matrix[i][j] = mat_2.matrix[i][j];
}

error_code get_rotation_x_matrix(matrix_t &yz, const double *changes)
{
    error_code result = no_errors;

    yz.n = MAT_SIZE;
    yz.m = MAT_SIZE;

    result = allocate_matrix(yz);
    if (!result)
    {
        yz.matrix[1][1] = cos(changes[0]);
        yz.matrix[1][2] = -sin(changes[0]);
        yz.matrix[2][1] = sin(changes[0]);
        yz.matrix[2][2] = cos(changes[0]);
        yz.matrix[0][0] = 1;
        yz.matrix[DIMENSION][DIMENSION] = 1;
    }

    return result;
}

error_code get_rotation_y_matrix(matrix_t &xz, const double *changes)
{
    error_code result = no_errors;

    xz.n = MAT_SIZE;
    xz.m = MAT_SIZE;
    result = allocate_matrix(xz);
    if (!result)
    {
        xz.matrix[0][0] = cos(changes[1]);
        xz.matrix[0][2] = sin(changes[1]);
        xz.matrix[2][0] = -sin(changes[1]);
        xz.matrix[2][2] = cos(changes[1]);
        xz.matrix[1][1] = 1;
        xz.matrix[DIMENSION][DIMENSION] = 1;
    }

    return result;
}

error_code get_rotation_z_matrix(matrix_t &xy, const double *changes)
{
    error_code result = no_errors;

    xy.n = MAT_SIZE;
    xy.m = MAT_SIZE;
    
    result = allocate_matrix(xy);
    if (!result)
    {
        xy.matrix[0][0] = cos(changes[2]);
        xy.matrix[0][1] = -sin(changes[2]);
        xy.matrix[1][0] = sin(changes[2]);
        xy.matrix[1][1] = cos(changes[2]);
        xy.matrix[2][2] = 1;
        xy.matrix[DIMENSION][DIMENSION] = 1;
    }

    return result;
}

void inverse_center_coords(double *center)
{
    for(int i = 0; i < DIMENSION; i++)
        center[i] *= -1;
}

error_code get_rotation_matrix_all_axes(matrix_t &transform_matrix, const double *changes)
{
    error_code result = no_errors;

    matrix_t xy;
    matrix_t yz;
    matrix_t xz;
    matrix_t res;
    matrix_t_init(res, MAT_SIZE, MAT_SIZE);

    result = get_rotation_x_matrix(yz, changes);
    if (!result)
        result = get_rotation_y_matrix(xz, changes);
    if (!result)
        result = get_rotation_z_matrix(xy, changes);
    if (!result)
        result = allocate_matrix(res);
    if (!result)
    {
        multiply_matrix(res, yz, xz);                              
        multiply_matrix(transform_matrix, res, xy);
    }

    free_matrix(xy);
    free_matrix(yz);
    free_matrix(xz);
    free_matrix(res);

    return result;
}

error_code get_transform_matrix_center_figure(matrix_t &transform_matrix, matrix_t &transform_center, double *center)
{
    error_code result = no_errors;

    matrix_t tmp;
    matrix_t_init(tmp, MAT_SIZE, MAT_SIZE);

    copy_matrix(transform_matrix, transform_center);

    result = allocate_matrix(tmp);
    if (!result)
    {
        inverse_center_coords(center);
        get_move_matrix(tmp, center);
        
        multiply_matrix(transform_center, tmp, transform_matrix);
            
        inverse_center_coords(center);
        get_move_matrix(tmp, center);

        multiply_matrix(transform_matrix, transform_center, tmp);
    }

    free_matrix(tmp);

    return result;
}

error_code get_rotation_transform_matrix_t(matrix_t &transform_matrix, changes_params_t &params)
{
    error_code result = no_errors;
    
    matrix_t rotate_center;
    matrix_t_init(rotate_center, MAT_SIZE, MAT_SIZE);

    result = allocate_matrix(rotate_center);
    if (!result)
        result = get_rotation_matrix_all_axes(rotate_center, params.changes);

    if (!result)
        result = get_transform_matrix_center_figure(transform_matrix, rotate_center, params.center);

    free_matrix(rotate_center);   
    
    return result;
}

void get_move_matrix(matrix_t &transform_matrix, double *changes)
{
    null_matrix(transform_matrix);
    
    for (int i = 0; i < transform_matrix.n; i++)
        transform_matrix.matrix[i][i] = 1;
    
    for (int i = 0; i < DIMENSION; i++)
        transform_matrix.matrix[transform_matrix.n - 1][i] = changes[i];
}


void get_scale_matrix(matrix_t &transform_matrix, const changes_params_t &params)
{
    for (int i = 0; i < DIMENSION; i++)
        transform_matrix.matrix[i][i] = params.changes[i];

    transform_matrix.matrix[DIMENSION][DIMENSION] = 1;   
}

error_code get_scale_transform_matrix_t(matrix_t &transform_matrix, changes_params_t &params)
{
    error_code result = no_errors;
    
    matrix_t scale_center;
    matrix_t_init(scale_center, MAT_SIZE, MAT_SIZE);
    
    result = allocate_matrix(scale_center);
    if (!result)
    {                  
        get_scale_matrix(scale_center, params);
        result = get_transform_matrix_center_figure(transform_matrix, scale_center, params.center);
    }
    
    free_matrix(scale_center);
    
    return result;
}

void multiply_point_to_matrix(point_t &res, point_t &point, const matrix_t &transform_matrix)
{
    for (int i = 0; i < point.n; i++)
    {
        for (int j = 0; j < transform_matrix.m; j++)
            res.coords[i] += point.coords[j] * transform_matrix.matrix[j][i];
    }
}

void swap_points(point_t &point_1, point_t &point_2)
{
    point_t tmp = point_t_init();
    tmp = point_1;
    point_1 = point_2;
    point_2 = tmp;
}

error_code transform_point(point_t &point, const matrix_t &transform_matrix)
{
    error_code result = no_errors;
    
    point_t res;
    result = allocate_point_t(res);

    if (!result)
    {
        multiply_point_to_matrix(res, point, transform_matrix);
        swap_points(res, point);
        free_point_t(res);
    }
    
    return result;
}

error_code transform_points(points_array_t &points, matrix_t &transform_matrix)
{
    error_code result = no_errors;

    for (int i = 0; i < points.amount && !result; i++)
        result = transform_point(points.array[i], transform_matrix);

    return result;
}

error_code math_model_t_rotate(math_model_t &figure, changes_params_t &params)
{
    if (model_is_void(figure.points))
        return error_void;

    error_code result = no_errors;

    matrix_t transform_matrix;
    matrix_t_init(transform_matrix, MAT_SIZE, MAT_SIZE);

    result = allocate_matrix(transform_matrix);
    if (!result)
    {
        get_center_coords(params, figure.points);
        result = get_rotation_transform_matrix_t(transform_matrix, params);

        if (!result)
            result = transform_points(figure.points, transform_matrix);
        
        free_matrix(transform_matrix);
    }

    return result;
}

void get_center_by_point(double *center, point_t &point)
{
    for (int j = 0; j < DIMENSION; j++)
        center[j] += point.coords[j];
}

void get_center_coords(changes_params_t &params, points_array_t &points)
{
    for (int i = 0; i < DIMENSION; i++)
        params.center[i] = 0;

    for (int i = 0; i < points.amount; i++)
        get_center_by_point(params.center, points.array[i]);

    for (int j = 0; j < DIMENSION; j++)
        params.center[j] /= points.amount;
}

error_code math_model_t_scale(math_model_t &figure, changes_params_t &params)
{
    error_code result = no_errors;

    if (model_is_void(figure.points))
        return error_void;

    matrix_t transform_matrix;
    matrix_t_init(transform_matrix, MAT_SIZE, MAT_SIZE);

    result = allocate_matrix(transform_matrix);
    if (!result)
    {
        get_center_coords(params, figure.points);
        get_scale_transform_matrix_t(transform_matrix, params);
    }

    result = transform_points(figure.points, transform_matrix);

    free_matrix(transform_matrix);

    return result;
}

error_code math_model_t_move(math_model_t &figure, changes_params_t &params)
{
    error_code result = no_errors;

    if (model_is_void(figure.points))
        return error_void;

    matrix_t transform_matrix;
    matrix_t_init(transform_matrix, MAT_SIZE, MAT_SIZE);

    result = allocate_matrix(transform_matrix);
    if (!result)
    {
        get_move_matrix(transform_matrix, params.changes);
        result = transform_points(figure.points, transform_matrix);
    }

    free_matrix(transform_matrix);

    return result;
}