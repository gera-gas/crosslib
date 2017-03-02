#ifndef APP_LAYOUT_HPP_
#define APP_LAYOUT_HPP_
/**
 * @file    AppLayout.hpp
 * @brief   Application base API.
 * @author  Gerasimov A.S.
 */
#include <stddef.h>
#include "typedef.h"

namespace sys {

/**
 * Application describe type.
 */
class AppLayout {
public:
	typedef void (*method_t) ( void* );

	AppLayout( BoardLayout * );

	void init  ( void );
	void start ( void );
	void fini  ( void );

protected:
	method_t virtual_init;
	method_t virtual_start;
	method_t virtual_fini;

private:
	BoardLayout *board_;
};

} /* namespace sys */

#endif /* APP_LAYOUT_HPP_ */
