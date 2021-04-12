#include "../inc/logic.h"
#include "../inc/mem_work.h"
#include "../inc/scan.h"
#include "../inc/model_transform.h"
#include "../inc/output.h"

error_code make_action(changes_params_t &params) 
{
    error_code result = no_errors;
    
    static math_model_t figure = math_model_t_init();
    
    switch (params.action)
    {
        case get_model:
            result = math_model_t_scan_from_file(figure, params.filename); 
            break;
        case save_model:
            result = math_model_t_save_to_file(figure, params.filename);
            break;
        case move_action:
            result = math_model_t_move(figure, params);
            break;
        case scale_action:
            result = math_model_t_scale(figure, params);
            break;
        case rotate_action:
            result = math_model_t_rotate(figure, params);
            break;
        case draw_action:
            result = math_model_t_draw(figure, params.painter);
            break;
        case free_memory:
            free_math_model_t(figure);
            break;
        default:
            break;
    }
    return result;
}