#include "../inc/polynomNewton.h"

int get_start_index(table_t *table, double x, int n)
{
    int index = 0;
    for (int i = 0; i < table->n - 1; i++)
    {
        if ((table->x[i] <= x && table->x[i + 1] >= x) || (table->x[i] >= x && table->x[i + 1] <= x))
            index = i;
    }
    index -= n / 2 - 1;
    if (index + n > table->n)
        index = table->n - n - 1;
    return (index < 0) ? 0 : index;
}

void swap(double **first, double **second)
{
    double *tmp = *first;
    *first = *second;
    *second = tmp;
}

error_code find_value_polynomial(double x, int n, double *p_x)
{
    error_code result = no_errors;
    n += 1;
    int start = 0;
    double *tmp = NULL;
    table_t table =
    {
        .x = NULL,
        .y = NULL,
    };
    result = allocate_and_fill_table(&table);
    if (!result)
    {
        start = get_start_index(&table, x, n);
        tmp = calloc(table.n, sizeof(double));
        if (!tmp)
            result = error_memory;
    }
    if (!result)
    {
        *p_x = table.y[start];
        memmove(tmp, table.y, table.n * sizeof(double));
        for (int i = start + 1; i < n + start; i++)
        {
            for (int j = start; j < n - i + start + start; j++)
            {
               
                tmp[j] = (tmp[j] - tmp[j + 1]) / (table.x[j] - table.x[j + i - start]);
            }
            double prom = tmp[start];
            for (int j = start; j < i; j++)
            {
                prom *= (x - table.x[j]);
            }
            *p_x += prom;
        }
    }
    free_table(&table);
    if (tmp)
        free(tmp);
    return result;
}
