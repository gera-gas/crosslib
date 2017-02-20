#ifndef UI_HPP_
#define UI_HPP_
/**
 * @file     ui.hpp
 * @brief    User interface halpers.
 * @author   Gerasimov A.S.
 * @note
 * Header dependencies:
 *
 * #include "tty.hpp"
 * #include "regexp.hpp"
 * #include "buffer.hpp"
 */
#include <stddef.h>

namespace sys {

/**
 * Type describe main context for users input.
 */
class UI_Input {
public:
	/**
	 * Type describe users input of various data.
	 */
	struct Parameter {
	public:
		/*
		 * List provided variables.
		 */
		LIST_ITEM(Parameter);

		/**
		 * @brief
		 * Create object of UI input parameters.
		 *
		 * @param buffer    : [out] address of output buffer.
		 * @param bufsize   : [in] output buffer size in sizeof(char).
		 * @param startinfo : [in] point to string with preliminary input information.
		 * @param filter    : [in] point to filter object or NULL (optional).
		 */
		Parameter ( char *buffer, size_t bufsize, const char *startinfo, FilterString *filter=NULL ) :
			prev(NULL), next(NULL),
			buffer_(buffer), bufsize_(bufsize),
			startinfo_(startinfo),
			filter_(filter)
		{
			;
		}

		/*
		 * Output buffer for user input.
		 * NOTE:
		 * In start process, buffer content will be
		 * displayed. If you don't wish it, clear buffer (fill zeros).
		 */
		char  *buffer_;
		size_t bufsize_;

		/*
		 * Preliminary output information.
		 */
		const char *startinfo_;

		/*
		 * [OPTIONAL]
		 * Etalon regular expression for input filter or 
		 * NULL if input without filter.
		 *
		 * For addition information see <regexp.h>
		 */
		FilterString *filter_;
	};

	/**
	 * @brief
	 * Create UI input descriptor.
	 *
	 * @param : [in] point to TTY object.
	 */
	UI_Input( TTY *tty ) :
		tty_(tty),
		paramlist_()
	{
		;
	}

	/**
	 * @brief
	 * Add UI input paramter object.
	 *
	 * @param : [in] point to UI_Input::Parameter object.
	 */
	void add_param ( Parameter *param )
	{
		paramlist_.add_tail( param );
	}

	/**
	 * @brief
	 * Start UI input procedure and manage of users input.
	 */
	void start ( void );

private:
	/*
	 * Point to tty dscriptor.
	 */
	TTY *tty_;

	/*
	 * Head of list with input parameters.
	 */
	List<Parameter> paramlist_;
};


/**
 * UI Menu context type.
 */
class UI_Menu {
public:
	/**
	 * UI Menu item type.
	 */
	class Item {
	public:
		/*
		 * List provided variables.
		 */
		LIST_ITEM(Item);

		/**
		 * Result type of menu item handler.
		 */
		enum HandlerResult {
			HANDLER_RESULT_STAY,
			HANDLER_RESULT_EXIT,
		};

		/*
		 * Item handler type.
		 * NOTE:
		 * It's not declarated here, because rtti is not avaliable.
		 *
		 * EXAMPLE:
		 * public: sys::UI_Menu::Item::enum HandlerResult handler (void);
		 */
		typedef enum HandlerResult (*handler_t) ( void );

		/**
		 * Create item object.
		 */
		Item ( const char *item_name, handler_t handler = reinterpret_cast<handler_t>(dummy_loop) ) :
			prev(NULL), next(NULL),
			name(item_name),
			handler_(handler) { }

		/*
		 * String with item name.
		 */
		const char *name;

		/*
		 * Call item handler.
		 */
		enum HandlerResult handler ( void )
		{
			return handler_( );
		}

	private:
		handler_t handler_;
	};

	/**
	 * Create UI menu descriptor.
	 *
	 * @param : [in] point to TTY object.
	 * @param : [in] point to string with menu title.
	 */
	UI_Menu ( TTY *tty, const char *title ) :
		tty_(tty),
		itemlist_(),
		current_item_(NULL),
		current_item_idx_(0),
		title_(title)
	{
		;
	}

	/**
	 * @brief
	 * Add UI menu paramter object.
	 *
	 * @param : [in] point to UI_Menu::Item object.
	 */
	void add_item ( Item *item )
	{
		itemlist_.add_tail( item );
	}

	/**
	 * @brief
	 * Start and manage UI menu.
	 */
	void start ( void );

private:
	/*
	 * Point to tty dscriptor.
	 */
	TTY *tty_;

	/*
	 * Head of list with menu items.
	 */
	List<Item> itemlist_;

	/*
	 * Point to current menu item.
	 */
	Item *current_item_;

	/*
	 * Number of current item starting by 0.
	 */
	size_t current_item_idx_;

	/*
	 *  String with menu title.
	 */
	const char *title_;
#if 0
	/**
	 * @brief
	 * Calculate index of current menu item.
	 */
	size_t get_item_index ( void );
#endif
	/**
	 * @brief
	 * Various down cursor position relative start item position (y=2).
	 *
	 * @param pos : [in] number of down step.
	 */
	void down_cursor ( size_t pos );

	/**
	 * @brief
	 * Indicate menu item.
	 *
	 * @param item_name : [in] point to string with item name.
	 */
	void indicate_item ( const char *item_name );

	/**
	 * @brief
	 * Display menu from parameters context.
	 *
	 * @param *menu_ctx : [in] point to menu context.
	 */
	void display_menu ( void );

	/**
	 * @brief
	 * Set previous cursor position on menu items.
	 */
	friend void item_point_move_up ( UI_Menu* );

	/**
	 * @brief
	 * Set next cursor position on menu items.
	 */
	friend void item_point_move_down ( UI_Menu* );

	/**
	 * @brief
	 * Execute cursor navigating on menu items.
	 *
	 * @param *sequence : [in] point to received ESC sequence.
	 */
	void navigate_on_menu ( const char *sequence );
};

#define UI_MENU_ITEM( n )\
	enum sys::UI_Menu::Item::HandlerResult n ( void )

#define UI_MENU_ITEM_STAY\
	sys::UI_Menu::Item::HANDLER_RESULT_STAY

#define UI_MENU_ITEM_EXIT\
	sys::UI_Menu::Item::HANDLER_RESULT_EXIT

} /* namespace sys */

#endif  /* UI_HPP_ */
