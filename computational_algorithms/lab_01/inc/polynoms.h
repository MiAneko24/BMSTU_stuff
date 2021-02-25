#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define LENGTH 8
#define EPS 1e-8
#define START_POW 1
#define END_POW 4

typedef struct 
{
    double *x;
    double *y;
    double *y_point;
    int type;
} table_t;

typedef enum 
{
    normal,
    root,
} mode;

typedef enum
{
    no_errors,
    error_memory,
    error_input,
} error_code;

typedef enum
{
    Newton = 1,
    Hermit = 2,
} type_table;

error_code scan_numbers(double *x, int *curr_mode);

double find_value_polynomial(double x, int n, error_code *result, mode current, int polynome_type);