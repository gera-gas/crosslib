/**
 *  @file    accessor.c
 *  @brief   Access control mechanism.
 *  @author  Gerasimov A.S.
 *  @date    2014-09-08 10:54:18
 */
#include "dummy.h"
#include "multitask/accessor.h"

/**
 * @brief
 * Contain point to function guaranted of atom execution.
 *
 * @example
 * entry - disable interrupt function.
 * leave - enable interrupt function.
 *
 * @note
 * Default contain point to empty function.
 */
critical_section_t critical_section = { dummy_empty, dummy_empty };
