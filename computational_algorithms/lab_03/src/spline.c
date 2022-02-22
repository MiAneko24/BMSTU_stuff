#include "../inc/spline.h"

error_code allocate_and_fill_table(table_t *table)
{
    table->n = END_NUM;
    table->x = calloc(table->n, sizeof(double));
    if (!table->x)
    {
        printf("Ошибка, не удалось выделить память\n");
        return error_memory;
    }
    table->y = calloc(table->n, sizeof(double));
    if (!table->y)
    {
        free(table->x);
        printf("Ошибка, не удалось выделить память\n");
        return error_memory;
    }
    for (int i = 0; i < table->n; i++)
    {
        table->x[i] = i;
        table->y[i] = i * i;
    }
    return no_errors;
}

error_code allocte_racing_table(table_t *racing)
{
    racing->n = END_NUM + 1;
    racing->x = calloc(racing->n, sizeof(double));
    if (!racing->x)
    {
        printf("Ошибка, не удалось выделить память\n");
        return error_memory;
    }
    racing->y = calloc(racing->n, sizeof(double));
    if (!racing->y)
    {
        free(racing->x);
        printf("Ошибка, не удалось выделить память\n");
        return error_memory;
    }
    racing->x[1] = 0;
    racing->y[1] = 0;
    return no_errors;
}

double h(double *x, int i)
{
    return (x[i] - x[i - 1]);
}

double f(table_t *table, int i)
{
    return 3 * ((table->y[i] - table->y[i - 1]) / \
    h(table->x, i) - (table->y[i - 1] - table->y[i - 2]) / h(table->x, i - 1));
}

void get_racing_coeffs(table_t *racing, table_t *table)
{
    double hi = 0;
    double hii = 0;
    for (int i = 1; i < racing->n - 1; i++)
    {
        hi = h(table->x, i);
        hii = h(table->x, i - 1);
        racing->x[i + 1] = - hi / (hii * racing->x[i] + \
        2 * (hii + hi));
        racing->y[i + 1] = (f(table, i) - hii * racing->y[i]) / \
        (hii * racing->x[i] + 2 * (hii + hi));
    }
}

void free_table(table_t *table)
{
    if (table->x)
    {
        free(table->x);
        table->x = NULL;
    }
    if (table->y)
    {
        free(table->y);
        table->y = NULL;
    }
    table->n = 0;
}

error_code get_c_coeff(table_t *table, spline_coeffs_t *coeffs, int i)
{
    error_code result = no_errors;
    
    table_t racing;
    result = allocte_racing_table(&racing);
    if (result)
        return result;
    
    get_racing_coeffs(&racing, table);
    coeffs->cii = 0;
    coeffs->ci = 0;
    for (int j = racing.n - 2; j >= i; j--)
    {
        coeffs->cii = coeffs->ci;
        coeffs->ci = racing.x[j + 1] * (coeffs->cii) + racing.y[j + 1];
    }
    free_table(&racing);
    return result;
}

error_code get_coeffs(table_t *table, spline_coeffs_t *coeffs, int i)
{ // вернуть 2 коэффициента с???
    error_code result = get_c_coeff(table, coeffs, i);
    if (result)
        return result;
    coeffs->a = table->y[i - 1];
    if (i != table->n - 1)
    {
        coeffs->b = (table->y[i] - table->y[i - 1]) / h(table->x, i) - h(table->x, i) * (coeffs->cii + 2 * coeffs->ci) / 3;
        coeffs->d = (coeffs->cii - coeffs->ci) / (3 * h(table->x, i));
    }
    else
    {
        coeffs->b = (table->y[i] - table->y[i - 1]) / h(table->x, i) - h(table->x, i) * 2 * coeffs->ci / 3;
        coeffs->d = -coeffs->ci / (3 * h(table->x, i));
    }
    return result;
}

double get_spline_result(table_t *table, spline_coeffs_t *coeffs, double x, int i)
{
    double hi = x - table->x[i - 1];
    
    return coeffs->a + coeffs->b * hi + coeffs->ci * hi * hi + coeffs->d * hi * hi * hi;
}

int get_interval_index(table_t *table, double x)
{
    int index = 0;
    for (int i = 0; (i < table->n - 1) && (x > table->x[i]); i++)
    {
        index = i;
    }
    return index + 1;
}

error_code get_value_spline(double *value, double x)
{
    error_code result = no_errors;
    table_t table;
    result = allocate_and_fill_table(&table);
    if (result)
        return result;
    int i = get_interval_index(&table, x);
    spline_coeffs_t coeffs;
    result = get_coeffs(&table, &coeffs, i);
    if (!result)
    {
        *value = get_spline_result(&table, &coeffs, x, i);
    }
    free_table(&table);
    return result;
}