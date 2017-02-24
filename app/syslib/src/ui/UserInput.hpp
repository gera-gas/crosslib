#ifndef USER_INPUT_HPP_
#define USER_INPUT_HPP_
/**
 * @file     UserInput.hpp
 * @brief    User interface halpers.
 * @author   Gerasimov A.S.
 * @note
 * Header dependencies:
 *
 * #include "io/tty/TeleType.hpp"
 * #include "regexp/FilterString.hpp"
 * #include "buffer/List.hpp"
 */
#include <stddef.h>

namespace ui {

/**
 * Type describe main context for users input.
 */
class UserInput {
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
		 * Create object of UI input parameters.
		 */
		Parameter ( char *, size_t, const char *, regexp::FilterString * );

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
		regexp::FilterString *filter_;
	};

	/**
	 * @brief
	 * Create UI input descriptor.
	 *
	 * @param : [in] point to TTY object.
	 */
	UserInput( tty::TeleType *tty ) :
		tty_(tty),
		paramlist_()
	{
		;
	}

	/**
	 * @brief
	 * Add UI input paramter object.
	 *
	 * @param : [in] point to UserInput::Parameter object.
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
	tty::TeleType *tty_;

	/*
	 * Head of list with input parameters.
	 */
	buffer::List<Parameter> paramlist_;
};

} /* namespace ui */

#endif  /* USER_INPUT_HPP_ */
