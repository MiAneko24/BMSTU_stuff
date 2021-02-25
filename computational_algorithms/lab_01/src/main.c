#include "../inc/polynoms.h"

int main(void)
{
    error_code result = no_errors;
    double x = 0;
    int curr_mode = normal;
    result = scan_numbers(&x, &curr_mode);
    if (!result && curr_mode == normal)
    {
        printf("Значения полиномов Ньютона и Эрмита при различных степенях\n"
               "┌─────┬────────────┬────────────┐\n"
               "│  n  │   Ньютон   │    Эрмит   │\n"
               "├─────┼────────────┼────────────┤\n");

        for (int i = START_POW; i <= END_POW && !result; i++)
        {
            //printf("i=%d\n", i);
            printf("│  %d  │ %10.6f │ %10.6f │\n", i, \
            find_value_polynomial(x, i, &result, curr_mode, Newton),
            find_value_polynomial(x, i, &result, curr_mode, Hermit));
        }
        printf("└─────┴────────────┴────────────┘\n");
    }
    else if (!result)
    {
        printf("Корень заданной табличной функции при различных степенях полинома Ньютона при обратной интерполяции\n"
               "┌─────┬────────────┐\n"
               "│  n  │   Корень   │\n"
               "├─────┼────────────┤\n");

        for (int i = START_POW; i <= END_POW && !result; i++)
        {
            printf("│  %d  │ %10.6f │\n", i, \
            find_value_polynomial(0, i, &result, curr_mode, Newton));
        }
        printf("└─────┴────────────┘\n");
    
    }
    return result;
}   