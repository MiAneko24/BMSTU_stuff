#include "../inc/polynoms.h"

int main(void)
{
    error_code result = no_errors;
    double x = 1.5;
    double y = 1.5;
    printf("Значение функции z(x, y) при различных степенях аппроксимирующих полиномов для x = %3.1f, y = %3.1f\n"
            "┌─────┬────────────┐\n"
            "│  n  │  Значение  │\n"
            "├─────┼────────────┤\n", x, y);

    for (int i = START_POW; i <= END_POW && !result; i++)
    {
        printf("│  %d  │ %10.6f │\n", i, \
        find_value_polynomial(x, i, y, i, &result));
    }
    printf("└─────┴────────────┘\n");
    
    return result;
}   