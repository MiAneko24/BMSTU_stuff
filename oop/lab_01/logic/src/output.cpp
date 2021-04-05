#include "../inc/output.h"
#include <QPainter>
#include <QtWidgets/QWidget>

void print_amount_and_points_to_file(points_array_t &points, FILE *f)
{
    fprintf(f, "%d\n", points.amount);
    for (int i = 0; i < points.amount; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
            fprintf(f, "%.4lf ", points.array[i].coords[j]);
        fprintf(f, "\n");
    }
}

void print_amount_and_connections_to_file(matrix_t &connection, FILE *f)
{

    fprintf(f, "%d\n", connection.n);
    for (int i = 0; i < connection.n; i++)
    {
        for (int j = 0; j < connection.m; j++)
            fprintf(f, "%d ", (int) connection.matrix[i][j]);
        fprintf(f, "\n");
    }
}

error_code math_model_t_save_to_file(math_model_t &figure, char *filename)
{
    if (model_is_void(figure))
        return error_void;

    error_code result = no_errors;

    FILE *f = fopen(filename, "w");
    if (f == NULL)
        return error_file;

    print_amount_and_points_to_file(figure.points, f);
    fclose(f);

    return result;
}

void draw_line_by_coords(QPainter *painter, double x1, double y1, double x2, double y2)
{
    painter->drawLine(x1, y1, x2, y2);
}

void draw_line_by_points(QPainter *painter, point_t &point_1, point_t &point_2)
{
    draw_line_by_coords(
        painter,
        point_1.coords[0], 
        point_1.coords[1],
        point_2.coords[0],
        point_2.coords[1]
        );
}

error_code math_model_t_draw(math_model_t &figure, QPainter *painter)
{
    if (model_is_void(figure))
        return error_void;

    int ind_1 = 0;
    int ind_2 = 0;
    for (int i = 0; i < figure.connection.n; i++)
    {
        ind_1 = (int) figure.connection.matrix[i][0];
        ind_2 = (int) figure.connection.matrix[i][1];
        draw_line_by_points(painter, figure.points.array[ind_1], figure.points.array[ind_2]);
    }
    
    return no_errors;
}