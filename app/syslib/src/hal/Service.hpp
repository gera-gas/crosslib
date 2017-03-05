#ifndef SERVICE_HPP_
#define SERVICE_HPP_
/**
 * @file   Service.hpp
 * @author Gerasimov A.S.
 * @brief  Service Layout.
 * @note   This is middle layer between application and hardware layers.
 */
#include <stddef.h>

namespace hal {

/**
 * Service layout class.
 */
class Service : public Module
{
public:
	Service( Board* );

	void init ( void );
	void fini ( void );
private:
	static int m_object_counter;

	Board *m_board;
};

} /* namespace hal */

#endif /* SERVICE_HPP_ */