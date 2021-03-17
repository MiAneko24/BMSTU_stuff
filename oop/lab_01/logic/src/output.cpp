#include "../inc/output.h"
#include <QPainter>
#include <QtWidgets/QWidget>

error_code save_to_file(math_model_t &figure, char *filename)
{
    error_code result = no_errors;
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        result = error_file;
    }
    else
    {
        fprintf(f, "%d\n", figure.dimensional_coords.n);
        for (int i = 0; i < figure.dimensional_coords.n; i++)
        {
            for (int j = 0; j < DIMENSION; j++)
                fprintf(f, "%.4lf ", figure.dimensional_coords.matrix[i][j]);
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
    }
    return result;
}

void draw_model(math_model_t &figure, QPainter *painter)
{
    for (int i = 0; i < figure.connection.n; i++)
    {
        painter->drawLine(
            figure.dimensional_coords.matrix[(int)figure.connection.matrix[i][0]][0], 
            figure.dimensional_coords.matrix[(int)figure.connection.matrix[i][0]][1],
            figure.dimensional_coords.matrix[(int)figure.connection.matrix[i][1]][0],
            figure.dimensional_coords.matrix[(int)figure.connection.matrix[i][1]][1]
            );
    }
}