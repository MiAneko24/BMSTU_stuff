#include "../inc/polynoms.h"

void free_table(table_t *table)
{
    if (table->x)
        free(table->x);
    if (table->y)
        free(table->y);
    if (table->y_point)
        free(table->y_point);
}

error_code get_table(table_t *table)
{
    error_code result = no_errors;
    table->x = calloc(LENGTH * table->type, sizeof(double));
    if (!table->x)
    {
        result = error_memory;
    }
    else
    {
        table->y = calloc(LENGTH * table->type, sizeof(double));
        if (!table->y)
        {
            result = error_memory;
        }
        else
        {
            table->y_point = calloc(LENGTH, sizeof(double));
            if (!table->y_point)
            {
                result = error_memory;
            }
        }
    }
    if (!result)
    {
        double cnt = 0;
        for (int i = 0; i < LENGTH * table->type; i++)
        {
            table->x[i] = cnt;
            if ((table->type == Hermit && i % 2 == 1) || table->type == Newton)
                cnt += 0.15;
        }
        int i = 0;
        for (int j = 0; j < table->type; j++)
            table->y[i + j] = 1;
        i += table->type;
        for (int j = 0; j < table->type; j++)
            table->y[i + j] = 0.838771;
        i += table->type;
        for (int j = 0; j < table->type; j++)
            table->y[i + j] = 0.655336;
        i += table->type;
        for (int j = 0; j < table->type; j++)
            table->y[i + j] = 0.450447;
        i += table->type;
        for (int j = 0; j < table->type; j++)
            table->y[i + j] = 0.225336;
        i += table->type;
        for (int j = 0; j < table->type; j++)
            table->y[i + j] = -0.018310;
        i += table->type;
        for (int j = 0; j < table->type; j++)
            table->y[i + j] = -0.278390;
        i += table->type;
        for (int j = 0; j < table->type; j++)
            table->y[i + j] = -0.552430;
        table->y_point[0] = -1;
        table->y_point[1] = -1.14944;
        table->y_point[2] = -1.29552;
        table->y_point[3] = -1.43497;
        table->y_point[4] = -1.56464;
        table->y_point[5] = -1.68164;
        table->y_point[6] = -1.78333;
        table->y_point[7] = -1.86742;
    }
    return result;
}

int get_start_index(table_t *table, double x, int n)
{
    int index = 0;
    for (int i = 0; i < LENGTH * table->type - 1; i++)
    {
        if ((table->x[i] <= x && table->x[i + 1] >= x) || (table->x[i] >= x && table->x[i + 1] <= x))
            index = i;
    }
    index -= n / 2 - 1;
    if (index + n > LENGTH * table->type)
        index = LENGTH * table->type - n - 1;
    return (index < 0) ? 0 : index;
}

void swap(double **first, double **second)
{
    double *tmp = *first;
    *first = *second;
    *second = tmp;
}

double find_value_polynomial(double x, int n, error_code *result, mode current, int polynome_type)
{
    double p_x = 0;
    n += 1;
    int start = 0;
    double *tmp = NULL;
    table_t table =
    {
        .x = NULL,
        .y = NULL,
        .y_point = NULL,
        .type = polynome_type,
    };
    *result = get_table(&table);
    if (!*result)
    {
        if (current == root)
        {
            swap(&table.x, &table.y);
        }
        start = get_start_index(&table, x, n);
        tmp = calloc(LENGTH * table.type, sizeof(double));
        if (!tmp)
            *result = error_memory;
    }
    if (!*result)
    {
        p_x = table.y[start];
        memmove(tmp, table.y, LENGTH * table.type * sizeof(double));
        for (int i = start + 1; i < n + start; i++)
        {
            for (int j = start; j < n - i + start + start; j++)
            {
                if (table.type == Hermit && fabs(tmp[j] - tmp[j + 1]) < EPS)
                {    
                    tmp[j] = table.y_point[j / 2];
                }
                else
                {
                    tmp[j] = (tmp[j] - tmp[j + 1]) / (table.x[j] - table.x[j + i - start]);
                }
            }
            double prom = tmp[start];
            for (int j = start; j < i; j++)
            {
                prom *= (x - table.x[j]);
            }
            p_x += prom;
        }
    }
    free_table(&table);
    if (tmp)
        free(tmp);
    return p_x;
}

error_code scan_numbers(double *x, int *curr_mode)
{
    error_code result = no_errors;
    printf("Введите режим работы:\n"
    "0 - поиск значения полинома в заданной точке\n"
    "1 - поиск корня заданной функции\n");
    int check = scanf("%d", curr_mode);
    if (check != 1 || *curr_mode < 0 || *curr_mode > 1)
    {
        result = error_input;
        printf("Ошибка, режим работы - целое число (0 или 1)\n");
    }
    if (!result && *curr_mode == normal)
    {
        printf("Введите точку, в которой нужно найти значение полинома: ");
        check = scanf("%lf", x);
        if (check != 1)
        {
            printf("Ошибка, точка для поиска значения полинома должна быть вещественным числом\n");
            result = error_input;
        }
    }
    return result;
}
