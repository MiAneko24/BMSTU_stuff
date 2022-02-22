#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define LENGTH 5
#define EPS 1e-8
#define START_POW 1
#define END_POW 3

typedef struct 
{
    double *x;
    double *y;
    double **z;
} table_t;

typedef enum
{
    no_errors,
    error_memory,
    error_input,
} error_code;

double find_value_polynomial(double x, int nx, double y, int ny, error_code *result);