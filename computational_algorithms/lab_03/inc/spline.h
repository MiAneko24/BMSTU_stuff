#ifndef SPLINE_H
#define SPLINE_H
#include "error_code.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

error_code get_value_spline(double *value, double x);

error_code allocate_and_fill_table(table_t *table);

void free_table(table_t *table);

#endif