#ifndef OUTPUT_H
#define OUTPUT_H
#include "logic.h"
#include "model_transform.h"

error_code math_model_t_save_to_file(math_model_t &figure, char *filename);

error_code math_model_t_draw(math_model_t &figure, QPainter *painter);

#endif