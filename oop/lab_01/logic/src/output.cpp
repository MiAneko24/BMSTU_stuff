#include "../inc/output.h"
#include <QPainter>
#include <QtWidgets/QWidget>

error_code math_model_t_save_to_file(math_model_t &figure, char *filename)
{
    if (!figure.inited)
        return error_void;
    error_code result = no_errors;
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        return error_file;
    }
    fprintf(f, "%d\n", figure.points.amount);
    for (int i = 0; i < figure.points.amount; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
            fprintf(f, "%.4lf ", figure.points.array[i].coords[j]);
        fprintf(f, "\n");
    }
    fprintf(f, "%d\n", figure.connection.n);
    for (int i = 0; i < figure.connection.n; i++)
    {
        for (int j = 0; j < figure.connection.m; j++)
            fprintf(f, "%d ", (int) figure.connection.matrix[i][j]);
        fprintf(f, "\n");
    }
    fclose(f);
    return result;
}

void draw_line(QPainter *painter, double x1, double y1, double x2, double y2)
{
    painter->drawLine(x1, y1, x2, y1);
}

error_code math_model_t_draw(math_model_t &figure, QPainter *painter)
{
    if (!figure.inited)
        return error_void;
    for (int i = 0; i < figure.connection.n; i++)
    {
        draw_line(
            painter,
            figure.points.array[(int)figure.connection.matrix[i][0]].coords[0], 
            figure.points.array[(int)figure.connection.matrix[i][0]].coords[1],
            figure.points.array[(int)figure.connection.matrix[i][1]].coords[0],
            figure.points.array[(int)figure.connection.matrix[i][1]].coords[1]
            );
    }
    return no_errors;
}