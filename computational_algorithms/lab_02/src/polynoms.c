#include "../inc/polynoms.h"

void free_table(table_t *table)
{
    if (table->x)
        free(table->x);
    if (table->y)
        free(table->y);
    if (table->z)
        free(table->z);
}

error_code memory_allocation(table_t *table)
{
    error_code result = no_errors;
    table->x = calloc(LENGTH, sizeof(double));
    if (!table->x)
    {
        result = error_memory;
    }
    else
    {
        table->y = calloc(LENGTH, sizeof(double));
        if (!table->y)
            result = error_memory;
    }
    if (!result)
    {
        table->z = malloc(LENGTH * sizeof(double *) + LENGTH * LENGTH * sizeof(double));
        if (!table->z)
            result = error_memory;
        else
        {
            for (int i = 0; i < LENGTH; i++)
                table->z[i] = (double *) (((char *) table->z) + LENGTH * sizeof(double *) + LENGTH * i * sizeof(double));
        }
    }
    return result;
}

error_code get_table(table_t *table)
{
    error_code result = no_errors;
    result = memory_allocation(table);
    if (!result)
    {
        for (int i = 0; i < LENGTH; i++)
        {
            table->x[i] = i;
            table->y[i] = i;
        }
        for (int i = 0; i < LENGTH; i++)
        {
            for (int j = i; j < LENGTH; j++)
            {
                table->z[i][j] = i * i + j * j;
                table->z[j][i] = i * i + j * j;
            }
        }
    }
    return result;
}

int get_start_index(table_t *table, double x, int n)
{
    int index = 0;
    for (int i = 0; i < LENGTH - 1; i++)
    {
        if ((table->x[i] <= x && table->x[i + 1] >= x) || (table->x[i] >= x && table->x[i + 1] <= x))
            index = i;
    }
    index -= n / 2 - 1;
    if (index + n > LENGTH)
        index = LENGTH - n - 1;
    return (index < 0) ? 0 : index;
}

void swap(double **first, double **second)
{
    double *tmp = *first;
    *first = *second;
    *second = tmp;
}

double linear_interpolation(int start, double *tmp, double *x_line, double *y_line, int n, double x)
{
    double p_x = y_line[start];
    memmove(tmp, y_line, LENGTH * sizeof(double));
    for (int i = start + 1; i < n + start; i++)
    {
        for (int j = start; j < n - i + start + start; j++)
        {
            tmp[j] = (tmp[j] - tmp[j + 1]) / (x_line[j] - x_line[j + i - start]);
        }
        double prom = tmp[start];
        for (int j = start; j < i; j++)
        {
            prom *= (x - x_line[j]);
        }
        p_x += prom;
    }
    return p_x;
}

double find_value_polynomial(double x, int nx, double y, int ny, error_code *result)
{
    double p_x = 0;
    nx++;
    ny++;
    int start_x = 0;
    int start_y = 0;
    double *tmp = NULL;
    double *f = NULL;
    table_t table =
    {
        .x = NULL,
        .y = NULL,
        .z = NULL,
    };
    *result = get_table(&table);
    if (!*result)
    {
        start_x = get_start_index(&table, x, nx);
        swap(&table.x, &table.y);
        start_y = get_start_index(&table, y, ny);
        swap(&table.x, &table.y);
        tmp = calloc(LENGTH, sizeof(double));
        if (!tmp)
            *result = error_memory;
        else
        {
            f = calloc(LENGTH, sizeof(double));
            if (!f)
                *result = error_memory;
        }
    }
    if (!*result)
    {
        for (int i = start_y; i < start_y + ny; i++)
        {
            f[i] = linear_interpolation(start_x, tmp, table.x, table.z[i], nx, x);
        }
        p_x = linear_interpolation(start_y, tmp, table.y, f, ny, y);
    }
    free_table(&table);
    if (tmp)
        free(tmp);
    if (f)
        free(f);
    return p_x;
}
