### <a name="ui_input_anchor"></a>Example of UI_Input class using.
UI descriptor using [VT100](../io/README.md#io_anchor) such as TTY context.

```cpp
#include "memory.h"
#include "hal.hpp"
#include "io.hpp"
#include "tty.hpp"
#include "vt100.hpp"
#include "regexp.hpp"
#include "buffer.hpp"
#include "ui.hpp"

/*
 * Create parameter for user name input.
 */
sys::FilterString filter_name(
	sys::FilterString::TYPE_CUSTOM,
	"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM ." );

char buffer_name[20];
	
sys::UI_Input::Parameter name(
	buffer_name, sizeof(buffer_name),
	"Enter your full name: ",
	&filter_name );

/*
 * Create parameter for user age input.
 */
sys::FilterString filter_age( sys::FilterString::TYPE_DECCHAR );

char buffer_age[4]; //(3 + 1) 3 digits for age and 1 for '\0'.
	
sys::UI_Input::Parameter age(
	buffer_age, sizeof(buffer_age),
	"Enter your age: ",
	&filter_age );

/*
 * Create parameter for user message input.
 */
char buffer_msg[40];

sys::UI_Input::Parameter msg(
	buffer_msg, sizeof(buffer_msg),
	"Your message: " );

/* Create UI input descriptor. */
sys::UI_Input ui_input( &tty );

int main ( void )
{
	/* Prepare output buffer. */
	memset( buffer_name, 0, sizeof(buffer_name) );
	memset( buffer_age,  0, sizeof(buffer_age)  );
	memset( buffer_msg,  0, sizeof(buffer_msg)  );

	/* Add paramter to UI input handler. */
	ui_input.add_param( &name );
	ui_input.add_param( &age  );
	ui_input.add_param( &msg  );

	/* Handling user input. */
	ui_input.start( );

	/* Output input result. */
 	tty.snd( tty.esc_clear_screen );
 	tty.snd( tty.esc_cursor_home );
 
 	tty.snd( "Name: " );
 	tty.snd( buffer_name );
 	tty.snd( tty.newline );
 
 	tty.snd( "Age: " );
 	tty.snd( buffer_age );
 	tty.snd( tty.newline );
 
 	tty.snd( "Message: " );
 	tty.snd( buffer_msg );
 	tty.snd( tty.newline );

	return 0;
}
```
