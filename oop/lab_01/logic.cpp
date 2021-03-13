#include "logic.h"


error_code create_matrix(matrix_t &mat);

void move(math_model_t &figure, changes_params_t &params);

void print_mat(matrix_t &mat);
void get_center_coords(changes_params_t &params, math_model_t &figure);
void get_move_matrix(matrix_t &transform_matrix, changes_params_t &params);

void multiply_matrix(matrix_t &mat_1, matrix_t &mat_2, matrix_t &res)
{
   // error_code result = no_errors;
    res.n = mat_1.n;
    res.m = mat_2.m;
   // result = create_matrix(res);
    for (int i = 0; i < res.n; i++)
    {
        for (int j = 0; j < res.m; j++)
            for (int k = 0; k < mat_2.n; k++)
                res.matrix[i][j] += mat_1.matrix[i][k] * mat_2.matrix[k][j];
    }
   // return result;
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
        //printf("Memory error creation, sizes: %dx%d\n", mat.n, mat.m);
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
    //for (int i = 0; i < DIMENSION; i++)
    //{
    //    params.angle[i] *= M_PI/180;
    //}
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
        printf("rotation wthout point\n");
        print_mat(transform_matrix);
        null_matrix(xy);
        for(int i = 0; i < DIMENSION; i++)
            params.move[i] *= -1;
        get_move_matrix(xy, params);
        null_matrix(res);
        multiply_matrix(xy, transform_matrix, res);
        printf("first move\n");
        print_mat(res);
        for(int i = 0; i < DIMENSION; i++)
            params.move[i] *= -1;
        null_matrix(xy);
        get_move_matrix(xy, params);
        null_matrix(transform_matrix);
        multiply_matrix(res, xy, transform_matrix);
        printf("sec move\n");
        print_mat(transform_matrix);
    }
    free_matrix(xy);
    free_matrix(yz);
    free_matrix(xz);
    free_matrix(res);   
    return result;
}

void print_mat(matrix_t &mat)
{
    for (int i = 0; i < mat.n; i++)
    {
        printf("(");
        for (int j = 0; j < mat.m; j++)
            printf("%5.3lf; ", mat.matrix[i][j]);
        printf(")\n");
    }
    printf("\n");
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
            transform_matrix.matrix[i][i] = params.k[i];
        
        transform_matrix.matrix[DIMENSION][DIMENSION] = 1;
        get_move_matrix(move, params);
        multiply_matrix(move, transform_matrix, res);
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
    if (figure.prospect_coords.matrix)
    {
        free(figure.prospect_coords.matrix);
        figure.prospect_coords.matrix = NULL;
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
    figure.prospect_coords = figure.dimensional_coords;
    figure.connection =
    {
        .matrix = NULL,
        .n = figure.connections_amount,
        .m = PAIRS,
    };
    result = create_matrix(figure.dimensional_coords);
    if (!result)
        result = create_matrix(figure.prospect_coords);
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

//error_code scan_coords_from_file(FILE *f, math_model_t &figure)
//{
//    error_code result = no_errors;
//        for (int j = 0; j < DIMENSION && !result; j++)
//        {
//            result = scan_double_from_file(f, figure.dimensional_coords.matrix[i][j]);
//        }
//    }
//
//    return result;
//}

error_code scan_matrix_from_file(FILE *f, matrix_t &mat)
{
    error_code result = no_errors;
    printf("n=%d, m=%d\n", mat.n, mat.m);
    for (int i = 0; i < mat.n && !result; i++)
    {
        for (int j = 0; j < mat.m && !result; j++)
        {
            result = scan_double_from_file(f, mat.matrix[i][j]);
            //printf("i=%d, j=%d, res=%d, mat = %lf\n", i, j, result, mat.matrix[i][j]);
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
        printf("I'm at connection\n");
        for (int i = 0; i < figure.points_amount && !result; i++)
        {
            figure.dimensional_coords.matrix[i][DIMENSION] = 1;
        }
        result = scan_matrix_from_file(f, figure.connection);
        printf("I'm out\n");
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

error_code transpose_matrix(matrix_t &mat)
{
    error_code result = no_errors;
    matrix_t new_mat = 
    {
        .matrix = NULL,
        .n = mat.m,
        .m = mat.n,
    };
    result = create_matrix(new_mat);
    if (!result)
    {
        for (int i = 0; i < new_mat.n; i++)
            for (int j = 0; j < new_mat.m; j++)
                new_mat.matrix[i][j] = mat.matrix[j][i];
        free_matrix(mat);
        mat = {
            .matrix = new_mat.matrix,
            .n = new_mat.n,
            .m = new_mat.m,
        };
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

//void scale_points(matrix_t &mat, int index, matrix_t &transform_matrix)
//{
//    matrix_t prom = 
//    {
//        .matrix = &mat.matrix[index],
//        .n = 1,
//        .m = MAT_SIZE,
//    };
//    matrix_t res = 
//    {
//        .matrix = NULL,
//        .n = 0,
//        .m = 0,
//    };
//    //result = transpose_matrix(prom);
//    multiply_matrix(prom, transform_matrix, res);
//    for (int j = 0; j < MAT_SIZE; j++)
//        mat.matrix[index][j] = res.matrix[0][j];
//    free_matrix(res);
//    free_matrix(prom);
//}

void get_center_coords(changes_params_t &params, math_model_t &figure)
{
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
        get_center_coords(params, figure);
        for (int i = 0; i < DIMENSION; i++)
            printf("%lf; ", params.move[i]);
        printf("\n");
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

void print_model(math_model_t &figure)
{
    printf("Model rn: \n");
    for (int i = 0; i < figure.points_amount; i++)
    {
        printf("(");
        for (int j = 0; j < DIMENSION; j++)
            printf("%5.3lf; ", figure.dimensional_coords.matrix[i][j]);
        printf(")\n");
    }
    printf("\n");
}

void copy_matrix(matrix_t &mat_1, matrix_t &mat_2)
{
    for (int i = 0; i < mat_1.n; i++)
        for (int j = 0; j < mat_1.m; j++)
        {
            mat_1.matrix[i][j] = mat_2.matrix[i][j];
        }
}

void decrease_dimension(matrix_t &mat, int index)
{
    for (int j = 0; j < DIMENSION; j++)
        mat.matrix[index][j] /= mat.matrix[index][DIMENSION];
    for (int j = 0; j < PAIRS; j++)
        mat.matrix[index][j] /= mat.matrix[index][PAIRS];
}

error_code get_prospective_coords(math_model_t &figure)
{
    error_code result = no_errors;
    matrix_t transform_mat = 
    {
        .matrix = NULL,
        .n = MAT_SIZE,
        .m = MAT_SIZE,
    };
    result = create_matrix(transform_mat);
    if (!result)
    {
        transform_mat.matrix[2][3] = - 1 / CAMERA_Z;
        copy_matrix(figure.prospect_coords, figure.dimensional_coords);
        for (int i = 0; i < figure.prospect_coords.n && !result; i++)
        {
            result = transform_points(figure.prospect_coords, i, transform_mat);
        }
        for (int i = 0; i < figure.prospect_coords.n; i++)
            decrease_dimension(figure.prospect_coords, i);
    }
    free_matrix(transform_mat);
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
        printf("In work\n");
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
    if (!result && action != save_model && action != free_memory)
        result = get_prospective_coords(figure);
    if (result && result != error_file)
        free_math_model_t(figure);
    if (!result)
        print_model(figure);
    return result;
}


//
//int main(void)
//{
//    math_model_t figure;
//    error_code result = scan_from_file(figure);
//    if (!result)
//    {
//        print_model(figure);
//        changes_params_t params;// = {
//            //.move = {10, 10, 10},
//            //.k = {2,,
//            //.angle = {90, 0, 0},
//        //};
//        for (int i = 0; i < DIMENSION; i++)
//            params.k[i] = 2;
//        //params.angle[0] = 45;
//       // move(figure, params)
//        result = scale(figure, params);
//        //result = rotate(figure, params);
//        if (!result)
//            print_model(figure);
//    }
//    free_math_model_t(figure);
//    return result;
//}