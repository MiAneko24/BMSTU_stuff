#include "../inc/logic.h"

#define MAT_SIZE 4
#define PAIRS 2
#define LINE 1

error_code create_matrix(matrix_t &mat);

void move(math_model_t &figure, changes_params_t &params);

void print_mat(matrix_t &mat);
void get_center_coords(changes_params_t &params, math_model_t &figure);
void get_move_matrix(matrix_t &transform_matrix, changes_params_t &params);

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

void free_matrix(matrix_t &mat)
{
    if (!mat.matrix)
        free(mat.matrix);
    mat.n = 0;
    mat.m = 0;
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
        xy.matrix[0][0] = cos(params.angle[0]);
        xy.matrix[0][1] = -sin(params.angle[0]);
        xy.matrix[1][0] = sin(params.angle[0]);
        xy.matrix[1][1] = cos(params.angle[0]);
        xy.matrix[2][2] = 1;
        xy.matrix[DIMENSION][DIMENSION] = 1;
        result = create_matrix(yz);
    }
    if (!result)
    {
        yz.matrix[1][1] = cos(params.angle[1]);
        yz.matrix[1][2] = -sin(params.angle[1]);
        yz.matrix[2][1] = sin(params.angle[1]);
        yz.matrix[2][2] = cos(params.angle[1]);
        yz.matrix[0][0] = 1;
        yz.matrix[DIMENSION][DIMENSION] = 1;
        result = create_matrix(xz);
    }
    if (!result)
    {
        xz.matrix[0][0] = cos(params.angle[2]);
        xz.matrix[0][2] = -sin(params.angle[2]);
        xz.matrix[2][0] = sin(params.angle[2]);
        xz.matrix[2][2] = cos(params.angle[2]);
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
            params.move[i] *= -1;
        get_move_matrix(xy, params);
        null_matrix(res);
        multiply_matrix(xy, transform_matrix, res);
        for(int i = 0; i < DIMENSION; i++)
            params.move[i] *= -1;
        null_matrix(xy);
        get_move_matrix(xy, params);
        null_matrix(transform_matrix);
        multiply_matrix(res, xy, transform_matrix);
    }
    free_matrix(xy);
    free_matrix(yz);
    free_matrix(xz);
    free_matrix(res);   
    return result;
}

void get_move_matrix(matrix_t &transform_matrix, changes_params_t &params)
{
    for (int i = 0; i < transform_matrix.n; i++)
        transform_matrix.matrix[i][i] = 1;
    for (int i = 0; i < DIMENSION; i++)
        transform_matrix.matrix[transform_matrix.n - 1][i] = params.move[i];
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
            transform_matrix.matrix[i][i] = params.k[i];
        }
        for(int i = 0; i < DIMENSION; i++)
            params.move[i] *= -1;
        transform_matrix.matrix[DIMENSION][DIMENSION] = 1;
        get_move_matrix(move, params);
        multiply_matrix(move, transform_matrix, res);
        null_matrix(transform_matrix);
        for (int i = 0; i < DIMENSION; i++)
        {
            params.move[i] *= -1;
        }
        get_move_matrix(move,params);
        multiply_matrix(res, move, transform_matrix);
    }
    free_matrix(move);
    free_matrix(res);
    return result;
}

void free_math_model_t(math_model_t &figure)
{
    figure.points_amount = 0;
    if (figure.dimensional_coords.matrix)
    {
        free(figure.dimensional_coords.matrix);
        figure.dimensional_coords.matrix = NULL;
    }
    if (figure.connection.matrix)
    {
        free(figure.connection.matrix);
        figure.connection.matrix = NULL;
    }
}

error_code create_math_model_t(math_model_t &figure)
{
    error_code result = no_errors;
    figure.dimensional_coords = 
    {
        .matrix = NULL,
        .n = figure.points_amount,
        .m = MAT_SIZE,
    };
    figure.connection =
    {
        .matrix = NULL,
        .n = figure.connections_amount,
        .m = PAIRS,
    };
    result = create_matrix(figure.dimensional_coords);
    if (!result)
        result = create_matrix(figure.connection);
    if (result)
    {
        free_math_model_t(figure);
    }
    return result;
}

error_code scan_int_from_file(FILE *f, int &num)
{
    error_code result = no_errors;
    int check = fscanf(f, "%d", &num);
    if (check != 1)
    {
        result = error_file_input;
    }
    return result;
}

error_code scan_double_from_file(FILE *f, double &num)
{
    error_code result = no_errors;
    int check = fscanf(f, "%lf", &num);
    if (check != 1)
    {
        result = error_file_input;
    }
    return result;
}


error_code scan_matrix_from_file(FILE *f, matrix_t &mat)
{
    error_code result = no_errors;
    for (int i = 0; i < mat.n && !result; i++)
    {
        for (int j = 0; j < mat.m && !result; j++)
        {
            result = scan_double_from_file(f, mat.matrix[i][j]);
        }
    }

    return result;
}

error_code scan_from_file(math_model_t &figure)
{
    error_code result = no_errors;
    FILE *f = fopen("model.txt", "r");
    if (f == NULL)
    {
        result = error_file;
    }
    else
    {
        if (figure.points_amount != 0)
            free_math_model_t(figure);
        result = scan_int_from_file(f, figure.points_amount);
    }
    if (!result)
        result = scan_int_from_file(f, figure.connections_amount);
    if (!result)
    {
        result = create_math_model_t(figure);
    }
    if (!result)
    {
        figure.dimensional_coords.m -= 1;
        result = scan_matrix_from_file(f, figure.dimensional_coords);
    }
    if (!result)
    {
        figure.dimensional_coords.m += 1;
        for (int i = 0; i < figure.points_amount && !result; i++)
        {
            figure.dimensional_coords.matrix[i][DIMENSION] = 1;
        }
        result = scan_matrix_from_file(f, figure.connection);
    }
    if (result != error_file)
    {
        if (result)
        {
            free_math_model_t(figure);
        }
        fclose(f);
    }
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
    for (int i = 0; i < figure.points_amount && !result; i++)
    {
        result = transform_points(figure.dimensional_coords, i, transform_matrix);
    }
    free_matrix(transform_matrix);
    return result;
}

void get_center_coords(changes_params_t &params, math_model_t &figure)
{
    for (int i = 0; i < DIMENSION; i++)
        params.move[i] = 0;
    for (int i = 0; i < figure.dimensional_coords.n; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            params.move[j] += figure.dimensional_coords.matrix[i][j];
        }
    }
    for (int j = 0; j < DIMENSION; j++)
        params.move[j] /= figure.points_amount;
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
            params.move[i] = 0;
        get_center_coords(params, figure);
        get_scale_transform_matrix_t(transform_matrix, params);
    }
    for (int i = 0; i < figure.points_amount && !result; i++)
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
            figure.dimensional_coords.matrix[i][j] += params.move[j];
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

error_code save_to_file(math_model_t &figure)
{
    error_code result = no_errors;
    FILE *f = fopen("model.txt", "w");
    if (f == NULL)
    {
        result = error_file;
    }
    else
    {
        fprintf(f, "%d\n", figure.points_amount);
        fprintf(f, "%d\n", figure.connections_amount);
        for (int i = 0; i < figure.dimensional_coords.n; i++)
        {
            for (int j = 0; j < DIMENSION; j++)
                fprintf(f, "%.4lf ", figure.dimensional_coords.matrix[i][j]);
            fprintf(f, "\n");
        }
        for (int i = 0; i < figure.connection.n; i++)
        {
            for (int j = 0; j < figure.connection.m; j++)
                fprintf(f, "%d ", (int) figure.connection.matrix[i][j]);
            fprintf(f, "\n");
        }
        fclose(f);
    }
    return result;
}

error_code make_action(math_model_t &figure, changes_params_t &params, int action)
{
    error_code result = no_errors;
    switch (action)
    {
    case get_model:
        result = scan_from_file(figure);
        break;
    case save_model:
        result = save_to_file(figure);
        break;
    case move_action:
        move(figure, params);
        break;
    case scale_action:
        result = scale(figure, params);
        break;
    case rotate_action:
        result = rotate(figure, params);
        break;
    default:
        free_math_model_t(figure);
        break;
    }
    if (result && result != error_file)
        free_math_model_t(figure);
    return result;
}