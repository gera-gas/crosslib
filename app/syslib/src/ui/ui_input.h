#ifndef UI_INPUT_H_
#define UI_INPUT_H_
/**
 * @file     ui_input.h
 * @brief    User interface (UI) input handlers.
 * @author   Gerasimov A.S.
 * @note
 * Header dependencies:
 *
 * #include "buffer.h"
 * #include "io.h"
 * #include "regexp.h"
 */
#include <stddef.h>

#if 0
typedef struct ui_input_st {
	/*
	 * Point to display API object.
	 */
	displat_api_t displat_api;

	/*
	 * Output buffer for user input.
	 */
	buffer_t *buffer;

	/*
	 * Top X,Y startup position.
	 */
	coord_t  startpos;

	/*
	 * Etalon regular expression for input filter.
	 */
	regexp_sz_t  etalon;

	/*
	 * Preliminary output information.
	 */
	const char *info;

	/*
	 * Number exists chars in output buffer.
	 */
	size_t  len;

} ui_input_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif  /* UI_INPUT_H_ */
