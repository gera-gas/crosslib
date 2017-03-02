### <a name="hal_uart_anchor"></a>Example of how to create UART driver.

```cpp
#include "typedef.h"
#include "hal.hpp"

namespace device {

/**
 * Class describe UART driver.
 */
class Uart : public hal::Port {
public:
	/**
	 * IO control commands for UART.
	 */
	enum IOCtl {
		IOCTL_GET,
		IOCTL_SET,
	};

	/**
	 * General UART provided work mode.
	 */
	enum Mode {
		MODE_8N1  = 0x1,
		MODE_8E2  = 0x2,
		MODE_LOOP = 0x8,
	};

	/**
	 * General UART provided work baud.
	 */
	enum Baud {
		BAUD_4800   = 0x01,
		BAUD_9600   = 0x02,
		BAUD_19200  = 0x03,
		BAUD_38400  = 0x04,
		BAUD_57600  = 0x05,
		BAUD_115200 = 0x06,
	};

	/**
	 * UART specifically parameters.
	 */
	struct Param {
		enum Mode mode;
		enum Baud baud;
	};

	/**
	 * @brief
	 * Device contructor.
	 *
	 * @param basemem : [in] Base address of device.
	 */
	Uart( const void *basemem ) :
		Port( basemem ) {
		/*
		 * Set exported driver methods.
		 */
		virtual_init  = reinterpret_cast<void (*)(void*)>(uart_init);
		virtual_fini  = reinterpret_cast<void (*)(void*)>(uart_fini);
		virtual_ioctl = reinterpret_cast<bool (*)(void*,int,void*)>(uart_ioctl);

		virtual_tx_ready = reinterpret_cast<bool (*)(void*)>(uart_txrdy);
		virtual_rx_ready = reinterpret_cast<bool (*)(void*)>(uart_rxrdy);

		virtual_tx = reinterpret_cast<void (*)(void*,size_t)>(uart_tx);
		virtual_rx = reinterpret_cast<size_t (*)(void*)>(uart_rx);
	};

protected:
	/*
	 * UART memory map.
	 */
	struct MemMap {
		volatile uint32 control;
		volatile uint32 mode;

		volatile uint32 baud;
		volatile uint32 status;

		volatile uint32 rx;
		volatile uint32 tx;
	};

	/*
	 * Control register bits definition
	 * for UART map.
	 */
	enum RegCtrl {
		REG_CTRL_DISABLE = 0x10,
		REG_CTRL_ENABLE  = 0x00,
	};

	/*
	 * Status register bits definition.
	 */
	enum RegStatus {
		REG_STAT_TX = 0x01,
		REG_STAT_RX = 0x02,
	};

	/*
	 * UART methods implementation.
	 */
	friend void   uart_init  ( Uart * );
	friend void   uart_fini  ( Uart * );
	friend bool   uart_ioctl ( Uart *, int, void * );
	friend bool   uart_txrdy ( Uart * );
	friend bool   uart_rxrdy ( Uart * );
	friend void   uart_tx    ( Uart *, size_t );
	friend size_t uart_rx    ( Uart * );

private:
	/*
	 * Structure with device custom parameters.
	 */
	Param param_;
};


/**
 * Driver method for UART initialize.
 * Set default baud: 115200, mode: 8N1.
 */
void uart_init ( Uart *uart )
{
	Uart::MemMap *regs = reinterpret_cast<Map*>( const_cast<void*>(basemem_) );

	/* Unable UART CLK */
	regs->control = static_cast<uint32>(REG_CTRL_ENABLE);
    
	/* Set mode UART */
	regs->mode = static_cast<uint32>(mode);
    
	/* Set baud UART */
	regs->baud = static_cast<uint32>(baud);

	uart->param_.mode = UART::MODE_8N1;
	uart->param_.baud = UART::BAUD_115200;
}


/**
 * Driver method for UART deinitialize.
 */
void uart_fini ( Uart *uart )
{
	Uart::MemMap *regs = reinterpret_cast<Map*>( const_cast<void*>(basemem_) );

	/* Disable UART CLK */
	regs->control = static_cast<uint32>(REG_CTRL_DISABLE);
}


/**
 * @brief
 * UART IO command control function.
 *
 * @param obj   : [in] point to device object.
 * @param cmd   : [in] command to control (see UART_ioctl in uart.hpp).
 * @param param : [in] address of device configuration parameters structure.
 *
 * @retval true  : success.
 * @retval false : failed.
 */
bool uart_ioctl ( Uart *uart, int cmd, void *param )
{
	Uart::Param *uart_param = reinterpret_cast<Uart::Param*>(param);

	bool result = true;


	switch( cmd )
	{
	case Uart::IOCTL_GET:
		uart_param->mode = uart->param_.mode;
		uart_param->baud = uart->param_.baud;
	break;

	case Uart::IOCTL_SET:
		/*
		 * Check input parameters on current values.
		 */
		switch( uart_param->mode )
		{
		case Uart::MODE_8N1:
		case Uart::MODE_8E2:
		case Uart::MODE_LOOP:
		break;

		default:
			return false;
		}

		switch( uart_param->baud )
		{
		case Uart::BAUD_4800:
		case Uart::BAUD_9600:
		case Uart::BAUD_19200:
		case Uart::BAUD_38400:
		case Uart::BAUD_57600:
		case Uart::BAUD_115200:
		case Uart::BAUD_230400:
		case Uart::BAUD_460800:
		case Uart::BAUD_921600:
		break;

		default:
			return false;
		}

		uart->param_.mode = uart_param->mode;
		uart->param_.baud = uart_param->baud;
		/*
		 * Configure UART of new parameters.
		 */
		regs->mode = static_cast<uint32>(uart_param->mode);
		regs->baud = static_cast<uint32>(uart_param->baud);
	break;

	default:
		result = false;
	break;
	}

	return result;
}


/**
 * @brief
 * Return <true> if uart ready to TX.
 */
bool uart_txrdy ( Uart *uart )
{
	Uart::MemMap *regs = reinterpret_cast<Uart::MemMap*>( const_cast<void*>(uart->basemem_) );

	return ( regs->status & static_cast<uint32>(Uart::REG_STAT_TX) );
}


/**
 * @brief
 * Return <true> if exist data on RX.
 */
bool uart_rxrdy ( Uart *uart )
{
	Uart::MemMap *regs = reinterpret_cast<Uart::MemMap*>( const_cast<void*>(uart->basemem_) );

	return ( regs->status & static_cast<uint32>(Uart::REG_STAT_RX) );
}


/**
 * @brief
 * Write char to UART TX buffer.
 */
void uart_tx ( Uart *uart, size_t c )
{
	Uart::MemMap *regs = reinterpret_cast<Uart::MemMap*>( const_cast<void*>(uart->basemem_) );

	regs->tx = static_cast<uint32>(c);
}


/**
 * @brief
 * Read char from UART RX buffer.
 */
size_t uart_rx ( Uart *uart )
{
	Uart::MemMap *regs = reinterpret_cast<Uart::MemMap*>( const_cast<void*>(uart->basemem_) );

	return regs->rx;
}

} /* namespace devices */

int main ( void )
{
	/*
	 * UART parameters.
	 */
	device::Uart::Param uart_param;

	/*
 	 * UART device descriptor.
	 */
	device::Uart uart( (const void *)0x80004000 );

	return 0;
}
```
