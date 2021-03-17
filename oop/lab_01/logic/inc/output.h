#ifndef OUTPUT_H
#define OUTPUT_H
#include "logic.h"
#include "model_transform.h"

error_code save_to_file(math_model_t &figure, char *filename);

void draw_model(math_model_t &figure, QPainter *painter);

#endif