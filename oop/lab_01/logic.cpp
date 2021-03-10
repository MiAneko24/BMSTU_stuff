#include <iostream>
#include <fstream>
#include <cmath>

#define MAT_SIZE 4
#define DIMENSION 3
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
    matrix_t up_coords;
    matrix_t down_coords;
} math_model_t;


error_code create_matrix(matrix_t &mat);

void print_mat(matrix_t &mat);

error_code multiply_matrix(matrix_t &mat_1, matrix_t &mat_2, matrix_t &res)
{
    error_code result = no_errors;
    res.n = mat_1.n;
    res.m = mat_2.m;
    result = create_matrix(res);
    for (int i = 0; i < res.n && !result; i++)
    {
        for (int j = 0; j < res.m; j++)
            for (int k = 0; k < mat_2.n; k++)
                res.matrix[i][j] += mat_1.matrix[i][k] * mat_2.matrix[k][j];
    }
    return result;
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
    for (int i = 0; i < DIMENSION; i++)
    {
        params.angle[i] *= M_PI/180;
    }
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
        result = multiply_matrix(xy, yz, res);
        if (!result)
        {
            result = multiply_matrix(res, xz, transform_matrix);
        }
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

void get_scale_transform_matrix_t(matrix_t &transform_matrix, changes_params_t &params)
{
    for (int i = 0; i < DIMENSION; i++)
        transform_matrix.matrix[i][i] = params.k[i];
    transform_matrix.matrix[DIMENSION][DIMENSION] = 1;
}

void free_math_model_t(math_model_t &figure)
{
    if (figure.down_coords.matrix)
        free(figure.down_coords.matrix);
    if (figure.up_coords.matrix)
        free(figure.up_coords.matrix);
}

error_code create_math_model_t(math_model_t &figure)
{
    error_code result = no_errors;
    figure.down_coords = 
    {
        .matrix = NULL,
        .n = figure.amount / 2,
        .m = MAT_SIZE,
    };
    figure.up_coords = 
    {
        .matrix = NULL,
        .n = figure.amount / 2,
        .m = MAT_SIZE,
    };
    result = create_matrix(figure.up_coords);
    if (!result)
        result = create_matrix(figure.down_coords);
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

error_code scan_coords_from_file(FILE *f, math_model_t &figure)
{
    error_code result = no_errors;
    for (int i = 0; i < figure.amount && !result; i++)
    {
        if (i < figure.amount / 2)
        {
            figure.up_coords.matrix[i][DIMENSION] = 1;
            for (int j = 0; j < DIMENSION && !result; j++)
            {
                result = scan_double_from_file(f, figure.up_coords.matrix[i][j]);
            }
        }
        else
        {
            figure.down_coords.matrix[i - figure.amount / 2][DIMENSION] = 1;
            for (int j = 0; j < DIMENSION && !result; j++)
                result = scan_double_from_file(f, figure.down_coords.matrix[i - figure.amount / 2][j]);
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
        result = scan_int_from_file(f, figure.amount);
    }
    if (!result)
    {
        result = create_math_model_t(figure);
    }
    if (!result)
        result = scan_coords_from_file(f, figure);
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
        .n = 0,
        .m = 0,
    };
    if (!result)
    {
        result = multiply_matrix(prom, transform_matrix, res);
    };
    for (int j = 0; j < MAT_SIZE && !result; j++)
        mat.matrix[index][j] = res.matrix[0][j];
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
        result = get_rotation_transform_matrix_t(transform_matrix, params);
    for (int i = 0; i < figure.amount / 2 && !result; i++)
    {
        result = transform_points(figure.up_coords, i, transform_matrix);
        if (!result)
            result = transform_points(figure.down_coords, i, transform_matrix);
    }
    free_matrix(transform_matrix);
    return result;
}

error_code scale_points(matrix_t &mat, int index, matrix_t &transform_matrix)
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
        .n = 0,
        .m = 0,
    };
    //result = transpose_matrix(prom);
    if (!result)
    {
        result = multiply_matrix(prom, transform_matrix, res);
    }
    for (int j = 0; j < MAT_SIZE && !result; j++)
        mat.matrix[index][j] = res.matrix[0][j];
    free_matrix(res);
    free_matrix(prom);
    return result;
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
        get_scale_transform_matrix_t(transform_matrix, params);
    for (int i = 0; i < figure.amount / 2 && !result; i++)
    {
        result = transform_points(figure.up_coords, i, transform_matrix);
        if (!result)
            result = transform_points(figure.down_coords, i, transform_matrix);
    }
    free_matrix(transform_matrix);
    return result;
}

void move(math_model_t &figure, changes_params_t &params)
{
    for (int i = 0; i < figure.amount / 2; i++)
    {
        for (int j = 0; j < MAT_SIZE; j++)
        {
            figure.up_coords.matrix[i][j] += params.move[j];
            figure.down_coords.matrix[i][j] += params.move[j];
        }
    }
}

void print_model(math_model_t &figure)
{
    printf("Model rn: \n");
    for (int i = 0; i < figure.amount / 2; i++)
    {
        printf("(");
        for (int j = 0; j < DIMENSION; j++)
            printf("%5.3lf; ", figure.up_coords.matrix[i][j]);
        printf(")\n");
        printf("(");
        for (int j = 0; j < DIMENSION; j++)
            printf("%5.3lf; ", figure.down_coords.matrix[i][j]);
        printf(")\n");
    }
    printf("\n");
}

int main(void)
{
    math_model_t figure;
    error_code result = scan_from_file(figure);
    if (!result)
    {
        print_model(figure);
        changes_params_t params;// = {
            //.move = {10, 10, 10},
            //.k = {2,,
            //.angle = {90, 0, 0},
        //};
        for (int i = 0; i < DIMENSION; i++)
            params.k[i] = 2;
        //params.angle[0] = 45;
       // move(figure, params)
        result = scale(figure, params);
        //result = rotate(figure, params);
        if (!result)
            print_model(figure);
    }
    free_math_model_t(figure);
    return result;
}