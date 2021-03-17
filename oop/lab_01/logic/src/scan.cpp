#include "../inc/scan.h"
#include "../inc/mem_work.h"

error_code scan_int_from_file(int &num, FILE *f) // Считывание целого числа из файла
{
    error_code result = no_errors;
    int check = fscanf(f, "%d", &num);
    if (check != 1)
    {
        result = error_file_input;
    }
    return result;
}

error_code scan_double_from_file(double &num, FILE *f) // Считывание вещественного числа из файла
{
    error_code result = no_errors;
    int check = fscanf(f, "%lf", &num);
    if (check != 1)
    {
        result = error_file_input;
    }
    return result;
}


error_code scan_matrix_from_file(matrix_t &mat, FILE *f) // Считывание матрицы из файла
{
    error_code result = no_errors;
    for (int i = 0; i < mat.n && !result; i++)
    {
        for (int j = 0; j < mat.m && !result; j++)
        {
            result = scan_double_from_file(mat.matrix[i][j], f);
        }
    }

    return result;
}

void increase_coords_dimension(matrix_t &mat) // Расширение матрицы координат точек (добавление четвертой координаты, равной единице)
{
    for (int i = 0; i < mat.n; i++)  
    {                                
        mat.matrix[i][DIMENSION] = 1;
    }
}

error_code scan_amount_and_coords_points_from_file(matrix_t &dimensional_coords, FILE *f) // Считывание количества точек и их координат из файла
{
    error_code result = no_errors;
    result = scan_int_from_file(dimensional_coords.n, f);
    if (result)
        return result;
    
    dimensional_coords.matrix = NULL;
    dimensional_coords.m = MAT_SIZE;

    result = create_matrix(dimensional_coords);
    if (!result)
    {
        dimensional_coords.m -= 1;
        result = scan_matrix_from_file(dimensional_coords, f);
        if (!result)
        {
            dimensional_coords.m += 1;
            increase_coords_dimension(dimensional_coords);
        }
    }
    return result;
}

error_code scan_amount_and_connections_from_file(matrix_t &connection, FILE *f) // Считывание количества соединений вершин и их самих из файла
{
    error_code result = no_errors;
    result = scan_int_from_file(connection.n, f);
    if (result)
        return result;
    connection.matrix = NULL;
    connection.m = PAIRS;
    result = create_matrix(connection);
    if (!result)
        result = scan_matrix_from_file(connection, f);
    return result;
}

error_code scan_from_file(math_model_t &figure, char *filename) 
{
    error_code result = no_errors;
    FILE *f = fopen(filename, "r");
    math_model_t tmp;
    if (f == NULL)
    {
        result = error_file;
        return result; 
    }
    result = scan_amount_and_coords_points_from_file(tmp.dimensional_coords, f);
    if (!result)
    {
        result = scan_amount_and_connections_from_file(tmp.connection, f);
    }
    fclose(f);
    if (!result)
    {
        free_math_model_t(figure);
        copy_math_model_t(figure, tmp);
    }
    else
        free_math_model_t(tmp);
    return result;
}