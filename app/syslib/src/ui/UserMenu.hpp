#ifndef USER_MENU_HPP_
#define USER_MENU_HPP_
/**
 * @file     UserMenu.hpp
 * @brief    User interface halpers.
 * @author   Gerasimov A.S.
 * @note
 * Header dependencies:
 *
 * #include "io/tty/TeleType.hpp"
 * #include "buffer/List.hpp"
 */
#include <stddef.h>

namespace ui {

/**
 * UI Menu context type.
 */
class UserMenu {
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
	UserMenu ( tty::TeleType *tty, const char *title ) :
		tty_(tty),
		itemlist_(),
		current_item_(NULL),
		current_item_idx_(0),
		title_(title)
	{ }

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
	tty::TeleType *tty_;

	/*
	 * Head of list with menu items.
	 */
	buffer::List<Item> itemlist_;

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
	friend void item_point_move_up ( UserMenu* );

	/**
	 * @brief
	 * Set next cursor position on menu items.
	 */
	friend void item_point_move_down ( UserMenu* );

	/**
	 * @brief
	 * Execute cursor navigating on menu items.
	 *
	 * @param *sequence : [in] point to received ESC sequence.
	 */
	void navigate_on_menu ( const char *sequence );
};

#define UI_MENU_ITEM( n )\
	enum ui::UserMenu::Item::HandlerResult n ( void )

#define UI_MENU_ITEM_STAY\
	ui::UserMenu::Item::HANDLER_RESULT_STAY

#define UI_MENU_ITEM_EXIT\
	ui::UserMenu::Item::HANDLER_RESULT_EXIT

} /* namespace ui */

#endif  /* USER_MENU_HPP_ */
