#ifndef UI_INPUT_H_
#define UI_INPUT_H_
/**
 * @file     ui_input.h
 * @brief    User interface (UI) input handlers.
 * @author   Gerasimov A.S.
 * @note
 * Header dependencies:
 *
 * #include "tty.h"
 * #include "regexp.h"
 *
 * @example
 * 
 * char name[40] = { 0 };
 * char age[4] = { 0 };
 * char msg[80] = { 0 };
 * 
 * // Create VT-100 TTY descriptor and connect IO for them.
 * VT100_TTY( iotty, &ioctx );
 * 
 * // Create data for user various input.
 * ui_inparam_t inparam[] = {
 * 	{
 * 	.buffer = name,
 * 	.bufsize = sizeof(name),
 * 	.startinfo = "Enter your full name: ",
 * 	.filter = {
 * 		.type = FSTRING_TYPE_CUSTOM,
 * 		.custom = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM ." }
 * 	},
 * 	{
 * 	.buffer = age,
 * 	.bufsize = sizeof(age), //(3 + 1) 3 digits for age and 1 for '\0'.
 * 	.startinfo = "Enter your age: ",
 * 	.filter = {
 * 		.type = FSTRING_TYPE_DECCHAR,
 * 		.custom = NULL }
 * 	},
 * 	{
 * 	.buffer = msg,
 * 	.bufsize = sizeof(msg),
 * 	.startinfo = "Your message: ",
 * 	.filter = {
 * 		.type = FSTRING_TYPE_NONE,
 * 		.custom = NULL }
 * 	}
 * };
 * 
 * // Create main descriptor for user input.
 * ui_input_t input_ctx = {
 * 	&iotty,
 * 	inparam
 * };
 * 
 * int main ( void )
 * {
 * 	ui_input( &input_ctx, ARRAY_SIZE(inparam) );
 * 
 * 	iotty.m_snd( &iotty, iotty.esc_clear_screen, NULL );
 * 	iotty.m_snd( &iotty, iotty.esc_cursor_home,  NULL );
 * 
 * 	iotty.m_snd( &iotty, "Name: ", NULL );
 * 	iotty.m_snd( &iotty, name, NULL );
 * 	iotty.m_snd( &iotty, iotty.newline, NULL );
 * 
 * 	iotty.m_snd( &iotty, "Age: ", NULL );
 * 	iotty.m_snd( &iotty, age, NULL );
 * 	iotty.m_snd( &iotty, iotty.newline, NULL );
 * 
 * 	iotty.m_snd( &iotty, "Message: ", NULL );
 * 	iotty.m_snd( &iotty, msg, NULL );
 * 	iotty.m_snd( &iotty, iotty.newline, NULL );
 * }
 */
#include <stddef.h>
#include <stdbool.h>

/**
 * Type describe users input of various data.
 */
typedef struct ui_inparam_st {
	/*
	 * Output buffer for user input.
	 * NOTE:
	 * In start process, buffer content will be
	 * displayed. If you don't wish it, clear buffer (fill zeros).
	 */
	char  *buffer;
	size_t bufsize;

	/*
	 * Preliminary output information.
	 */
	const char *startinfo;

	/*
	 * [OPTIONAL]
	 * Etalon regular expression for input filter or 
	 * NULL if input without filter.
	 *
	 * for addition information see <regexp.h>
	 */
	fstring_t filter;

} ui_inparam_t;


/**
 * Type describe main context for users input.
 */
typedef struct ui_input_st {
	/*
	 * Point to tty dscriptor.
	 */
	tty_t *tty;

	/*
	 * Point to list with input parameters.
	 */
	ui_inparam_t *inparam;

} ui_input_t;


#ifdef __cplusplus
extern "C" {
#endif

void ui_input ( ui_input_t *input_ctx, size_t input_num );

#ifdef __cplusplus
}
#endif

#endif  /* UI_INPUT_H_ */
