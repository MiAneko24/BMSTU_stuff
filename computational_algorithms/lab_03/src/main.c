#include "../inc/scan.h"
#include "../inc/spline.h"
#include "../inc/polynomNewton.h"

int main(int argc, char **argv)
{
    error_code result = no_errors;
    double x = 0;
    double value = 0;
    double newton = 0;
    result = scan_number(&x);
    if (!result)
    {
        result = get_value_spline(&value, x);
        if (!result)
            result = find_value_polynomial(x, 3, &newton);
    }
    if (!result)
    {
        printf("Значения полиномов Ньютона и Эрмита при различных степенях\n"
               "┌─────┬─────────────────┬────────────┬─────────────────┐\n"
               "│  x  │ Точное значение │   Сплайн   │ Полином Ньютона │\n"
               "├─────┼─────────────────┼────────────┼─────────────────┤\n");

        printf("│%5.3lf│ %15.6lf │ %10.6lf │ %15.6lf │\n", x, x * x, value, newton);

        printf("└─────┴─────────────────┴────────────┴─────────────────┘\n");
    }
    return result;
}