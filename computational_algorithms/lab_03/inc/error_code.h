#ifndef ERROR_CODE_H
#define ERROR_CODE_H
#define END_NUM 11

typedef enum
{
    no_errors,
    error_input,
    error_memory,
} error_code;

typedef struct 
{
    double *x;
    double *y;
    int n;
} table_t;

typedef struct 
{
    double a;
    double b;
    double ci;
    double cii;
    double d;
} spline_coeffs_t;


#endif