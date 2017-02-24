### <a name="ui_input_anchor"></a>Example of UI_Input class using.
UI descriptor using [VT100](../io/README.md#io_anchor) such as TTY context.

```cpp
#include "memory.h"
#include "ui.hpp"

/*
 * Create parameter for user name input.
 */
regexp::FilterString filter_name(
	regexp::FilterString::TYPE_CUSTOM,
	"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM ." );

char buffer_name[20];

ui::UserInput::Parameter name(
	buffer_name, sizeof(buffer_name),
	"Enter your full name: ",
	&filter_name );

/*
 * Create parameter for user age input.
 */
regexp::FilterString filter_age( regexp::FilterString::TYPE_DECCHAR );

char buffer_age[4]; //(3 + 1) 3 digits for age and 1 for '\0'.
	
ui::UserInput::Parameter age(
	buffer_age, sizeof(buffer_age),
	"Enter your age: ",
	&filter_age );

/*
 * Create parameter for user message input.
 */
char buffer_msg[40];

ui::UserInput::Parameter msg(
	buffer_msg, sizeof(buffer_msg),
	"Your message: " );

/* Create UI input descriptor. */
ui::UserInput ui_input( &tty );

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

### <a name="ui_menu_anchor"></a>Example of UI_Menu class using.
UI descriptor using [VT100](../io/README.md#io_anchor) such as TTY context.

```cpp
#include "memory.h"
#include "ui.hpp"

/*
 * Create item-1 for UI menu.
 */
enum ui::UserMenu::Item::HandlerResult item1_handler ( void )
{
	App::io.puts( "ITEM-1 was selected ..." );
	App::io.getch( );

	return ui::UserMenu::Item::HANDLER_RESULT_STAY;
}

/*
 * Create item-2 for UI menu by special macros.
 */
UI_MENU_ITEM( item2_handler )
{
	App::io.puts( "ITEM-2 it's exit from menu, bye!" );
	App::io.getch( );

	return UI_MENU_ITEM_EXIT;
}

int main ( void )
{
	tty::VT100 tty( &App::io );

	/* Create menu item objects. */
	ui::UserMenu::Item item1( "ITEM-1", item1_handler );
	ui::UserMenu::Item item2( "ITEM-2", item2_handler );

	/* Create main menu descriptor. */
	ui::UserMenu ui_menu( &tty, "VT-100 DEMO MENU" );

	/* Add items to menu. */
	ui_menu.add_item( &item1 );
	ui_menu.add_item( &item2 );

	/* Run menu. */
	ui_menu.start( );

	return 0;
}
```
