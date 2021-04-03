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

error_code scan_points_array_from_file(points_array_t &points, FILE *f)
{
    error_code result = no_errors;
    for (int i = 0; i < points.amount && !result; i++)
        for (int j = 0; j < points.array[i].n && !result; j++)
        {
            result = scan_double_from_file(points.array[i].coords[j], f);
        }
    return result;
}

void increase_coords_dimension(points_array_t &points) // Расширение матрицы координат точек (добавление четвертой координаты, равной единице)
{
    for (int i = 0; i < points.amount; i++)  
    {                      
        points.array[i].n++;
        points.array[i].coords[DIMENSION] = 1;
    }
}

void decrement_coords_dimension(points_array_t &points)
{
    for (int i = 0; i < points.amount; i++)
        points.array[i].n--;
}

error_code scan_amount_and_coords_points_from_file(points_array_t &points, FILE *f) // Считывание количества точек и их координат из файла
{
    error_code result = no_errors;
    result = scan_int_from_file(points.amount, f);
    if (result)
        return result;

    result = create_points_array_t(points);
    if (!result)
    {
        decrement_coords_dimension(points);
        result = scan_points_array_from_file(points, f);
        if (!result)
        {
            increase_coords_dimension(points);
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

error_code math_model_t_scan_from_file(math_model_t &figure, char *filename) 
{
    error_code result = no_errors;
    FILE *f = fopen(filename, "r");
    math_model_t tmp;
    if (f == NULL)
    {
        result = error_file;
        return result; 
    }
    result = scan_amount_and_coords_points_from_file(tmp.points, f);
    if (!result)
    {
        result = scan_amount_and_connections_from_file(tmp.connection, f);
    }
    fclose(f);
    if (!result)
    {
        free_math_model_t(figure);
        figure = tmp;
    }
    else
        free_math_model_t(tmp);
    return result;
}