#include "../inc/scan.h"

error_code scan_number(double *x)
{
    error_code result = no_errors;
    printf("Введите точку из интервала [0; %d], значение функции в которой необходимо найти: ", END_NUM - 1);
    int check = scanf("%lf", x);
    if (check != 1)
    {
        printf("Точка должна быть вещественным числом\n");
        result = error_input;
    }
    if (*x < 0 || *x > END_NUM - 1)
    {
        printf("Ошибка, точка должна принадлежать интервалу [0; %d]\n", END_NUM - 1);
        result = error_input;
    }
    return result;
}