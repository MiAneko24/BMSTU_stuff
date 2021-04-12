#include "../inc/output.h"
#include <QPainter>
#include <QtWidgets/QWidget>

void print_point_to_file(point_t &point, FILE *f)
{
    for (int j = 0; j < DIMENSION; j++)
        fprintf(f, "%.4lf ", point.coords[j]);
}

void print_amount_and_points_to_file(points_array_t &points, FILE *f)
{
    fprintf(f, "%d\n", points.amount);
    for (int i = 0; i < points.amount; i++)
    {
        print_point_to_file(points.array[i], f);
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
    if (model_is_void(figure.points))
        return error_void;

    error_code result = no_errors;

    FILE *f = fopen(filename, "w");
    if (f == NULL)
        return error_file;

    print_amount_and_points_to_file(figure.points, f);
    print_amount_and_connections_to_file(figure.connection, f);
    fclose(f);

    return result;
}

void draw_line_by_coords(QPainter *painter, const double x1, const double y1, const double x2, const double y2)
{
    painter->drawLine(x1, y1, x2, y2);
}

void draw_line_by_points(const point_t &point_1, const point_t &point_2, QPainter *painter)
{
    draw_line_by_coords(
        painter,
        point_1.coords[0], 
        point_1.coords[1],
        point_2.coords[0],
        point_2.coords[1]
        );
}

void draw_lines_by_connections(points_array_t &points, matrix_t &connection, QPainter *painter)
{
    int ind_1 = 0;
    int ind_2 = 0;
    for (int i = 0; i < connection.n; i++)
    {
        ind_1 = (int) connection.matrix[i][0];
        ind_2 = (int) connection.matrix[i][1];
        draw_line_by_points(points.array[ind_1], points.array[ind_2], painter);
    }
}

error_code math_model_t_draw(math_model_t &figure, QPainter *painter)
{
    if (model_is_void(figure.points))
        return error_void;

    draw_lines_by_connections(figure.points, figure.connection, painter);

    return no_errors;
}