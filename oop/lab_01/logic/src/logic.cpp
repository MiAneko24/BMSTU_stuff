#include "../inc/logic.h"
#include "../inc/mem_work.h"
#include "../inc/scan.h"
#include "../inc/model_transform.h"
#include "../inc/output.h"
// в точке входа никаких посторонних функций!

error_code make_action(changes_params_t &params) 
{
    error_code result = no_errors;
    static math_model_t figure;
    if (figure.dimensional_coords.n == 0 && params.action != get_model)
    {
        result = error_void;
        return result;
    }
    
    switch (params.action)
    {
    case get_model:
        result = scan_from_file(figure, params.filename); // Добавить выбор файла на усмотрение юзера
        break;
    case save_model:
        result = save_to_file(figure, params.filename);
        break;
    case move_action:
        move(figure, params);
        break;
    case scale_action:
        result = scale(figure, params);
        break;
    case rotate_action:
        result = rotate(figure, params);
        break;
    case draw_action:
        draw_model(figure, params.painter);
        break;
    default:
        free_math_model_t(figure);
        break;
    }
    return result;
}