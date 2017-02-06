/**
 * @file     ui_input.c
 * @brief    User interface (UI) input handlers.
 * @author   Gerasimov A.S.
 */
#include "ui_input.h"


/*
 НАЗНАЧЕНИЕ:
 *  Осущесвляет обработку параметов меню.
 *
 ПАРАМЕТРЫ:
 *  1) вход/выход : menuparam_t : *ioparam - указатель на структуру параметров.
 *
 РЕЗУЛЬТАТ:
 *  1) bool_t : true  - все параметры обработаны;
 *  2) bool_t : false - отмена обработки (ввода) параметров.
 */
