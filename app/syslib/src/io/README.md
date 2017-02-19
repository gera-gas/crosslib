### <a name="io_anchor"></a>Example of how to create IO descriptor.
IO descriptor using [UART device](../hal/README.md#hal_uart_anchor) such as IO device.

```cpp
#include "typedef.h"
#include "hal.hpp"
#include "io.hpp"
#include "uart.hpp"

int main ( void )
{
	/*
 	 * IO descriptor.
	 */
	sys::InOut io( &uart );

	io.puts( "Hello World!" );
	/*
	 * Crete VT100 descriptor based on IO.
	 */
	sys::VT100 tty( &io );

	tty.snd( tty_->esc_clear_screen );
	tty.snd( tty_->esc_cursor_home );

	/*
	 * Move cursor down on 2 lines.
	 */
	tty.snd( tty_->esc_cursor_down, "2" );

	/*
	 * Set cursor position x=2, y=3.
	 */
	tty.cursor_set( 2, 3 );

	return 0;
}
```
