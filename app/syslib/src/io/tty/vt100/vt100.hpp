#ifndef VT100_HPP_
#define VT100_HPP_
/**
 * @file     Vt100.hpp
 * @brief    VT-100 IO service.
 * @author   Gerasimov A.S.
 */
#include <stddef.h>

namespace tty {

/**
 * General TTY type.
 */
class Vt100 : public TeleType {
public:
	/**
	 * @brief
	 * VT100 class constructor.
	 *
	 * @param [in] : address of IO object.
	 */
	Vt100( io::InOut *io );

private:
	/*
	 * VT100 Emplementation SND/RCV methods.
	 */
	friend size_t vt100_rcv ( Vt100 *tty, char *buffer, size_t bufsize );
	friend void   vt100_snd ( Vt100 *tty, const char *esc, const char *param );
};

} /* namespace tty */

#endif  /* VT100_HPP_ */
