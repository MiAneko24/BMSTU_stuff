#include "../inc/scan.h"
#include "../inc/mem_work.h"

error_code scan_int_from_file(int &num, FILE *f) // Считывание целого числа из файла
{
    error_code result = no_errors;

    int check = fscanf(f, "%d", &num);
    if (check != 1)
        result = error_file_input;
    
    return result;
}

error_code scan_double_from_file(double &num, FILE *f) // Считывание вещественного числа из файла
{
    error_code result = no_errors;
    
    int check = fscanf(f, "%lf", &num);
    if (check != 1)
        result = error_file_input;
    
    return result;
}

error_code scan_matrix_from_file(matrix_t &mat, FILE *f) // Считывание матрицы из файла
{
    error_code result = no_errors;
    
    for (int i = 0; i < mat.n && !result; i++)
        for (int j = 0; j < mat.m && !result; j++)
            result = scan_double_from_file(mat.matrix[i][j], f);
    
    return result;
}

error_code scan_point_from_file(point_t &point, FILE *f)
{
    error_code result = no_errors;

    for (int j = 0; j < point.n - 1 && !result; j++)
        result = scan_double_from_file(point.coords[j], f);
    
    return result;
}

error_code scan_points_from_file(points_array_t &points, FILE *f)
{
    error_code result = no_errors;
    
    for (int i = 0; i < points.amount && !result; i++)
        result = scan_point_from_file(points.array[i], f);
    
    return result;
}

void increase_point_coords_dimension(point_t &point)
{
    point.coords[DIMENSION] = 1;
}

void increase_points_coords_dimension(points_array_t &points) // Добавление четвертой координаты, равной единице, для каждой точки
{
    for (int i = 0; i < points.amount; i++)                      
        increase_point_coords_dimension(points.array[i]); 
}

error_code scan_amount_and_points_from_file(points_array_t &points, FILE *f) // Считывание количества точек и их координат из файла
{
    error_code result = no_errors;

    result = scan_int_from_file(points.amount, f);
    if (result)
        return result;

    result = allocate_points_array_t(points);
    if (!result)
    {
        result = scan_points_from_file(points, f);
        if (!result)
            increase_points_coords_dimension(points);
    }

    return result;
}

error_code scan_connections_from_file(matrix_t &connection, FILE *f) // Считывание количества соединений вершин и их самих из файла
{
    error_code result = no_errors;

    result = scan_int_from_file(connection.n, f);
    if (result)
        return result;
    if (connection.n <= 0)
        return error_file_input;

    connection.matrix = NULL;
    connection.m = PAIRS;

    result = allocate_matrix(connection);
    if (!result)
        result = scan_matrix_from_file(connection, f);

    return result;
}

error_code math_model_t_scan_from_file(math_model_t &figure, char *filename) 
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return error_file; 
        
    error_code result = no_errors;

    math_model_t tmp = math_model_t_init();

    result = scan_amount_and_points_from_file(tmp.points, f);
    if (!result)
    {
        result = scan_connections_from_file(tmp.connection, f);
        if (result)
        {
            free_points_t(tmp.points);
        }
    }
    fclose(f);

    if (!result)
    {
        free_math_model_t(figure);
        figure = tmp;
    }
 
    return result;
}