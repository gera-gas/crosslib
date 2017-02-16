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
			buffer_(buffer),
			bufsize_(bufsize),
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

		/*
		 * List provided variables.
		 */
		LIST_OBJ(Parameter);
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
	 * Start UI input procedure and manage
	 * of users input.
	 */
	void start ( void );

private:
	/*
	 * Point to tty dscriptor.
	 */
	TTY *tty_;

	/*
	 * Point to first parameter into list with input parameters.
	 */
	List<Parameter> paramlist_;
};

} /* namespace sys */

#endif  /* UI_HPP_ */
