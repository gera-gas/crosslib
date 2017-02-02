#ifndef HAL_H_
#define HAL_H_
/**
 *  @file     hal.h
 *  @brief    Hardware Abstraction Level (HAL).
 *  @author   Gerasimov A.S.
 *  @date     2013-08-07 15:26:14 +0400
 */
#include <stdbool.h>
#include <stddef.h>

/**
 * Device type.
 */
typedef enum {
	DEVTYPE_IFACE,
	DEVTYPE_SERVICE
} devtype_t;


/**
 * Type describe hardware device.
 */
typedef struct device_st {
	struct device_st *next;

	devtype_t type;

	union {
		struct iface_st *driver;
		/*
		 * Device who was implementation sush as interface device.
		 */
		struct device_st *device;
	} iface;

	void *basemem;
	void *param;

} device_t;


/**
 * Type describe interface device and
 * modules for interaction.
 */
typedef struct iface_st {
	struct iface_st *next;

	/*
	 * Startup device and configure by default.
	 */
	union {
		void (*f) ( device_t * );
		void *p;
	} init;

	/*
	 * Custom configuration and control of device.
	 */
	union {
		bool (*f) ( device_t *, int, void * );
		void *p;
	} cmd;

	union {
		bool (*f) ( device_t * );
		void *p;
	} tx_ready;

	union {
		bool (*f) ( device_t * );
		void *p;
	} rx_ready;

	union {
		  void (*fchar)  ( device_t *, int );
		size_t (*fblock) ( device_t *, const void *, size_t );
		void *p;
	} tx;

	union {
		   int (*fchar)  ( device_t * );
		size_t (*fblock) ( device_t *, void *, size_t );
		void *p;
	} rx;

	/*
	 * Disable and power down function.
	 */
	union {
		void (*f) ( device_t * );
		void *p;
	} fini;

} iface_t;

/*
 * Call <init/fini> methods of device driver.
 */
#define IFACE_INIT( dev ) dev.iface.driver->init.f( &dev )
#define IFACE_FINI( dev ) dev.iface.driver->fini.f( &dev )

#define pIFACE_INIT( dev ) dev->iface.driver->init.f( &dev )
#define pIFACE_FINI( dev ) dev->iface.driver->fini.f( &dev )

/*
 * Call <cmd> methods of device driver.
 */
#define IFACE_CMD( dev, cmd, par ) dev.iface.driver->cmd.f( &dev, cmd, par )
#define pIFACE_CMD( dev, cmd, par ) dev->iface.driver->cmd.f( &dev, cmd, par )

/*
 * Call tx/rx ready methods of device driver.
 */

#define IFACE_TX_READY( dev ) dev.iface.driver->tx_ready.f( &dev )
#define IFACE_RX_READY( dev ) dev.iface.driver->rx_ready.f( &dev )

#define pIFACE_TX_READY( dev ) dev->iface.driver->tx_ready.f( &dev )
#define pIFACE_RX_READY( dev ) dev->iface.driver->rx_ready.f( &dev )

/*
 * Call tx/rx char methods of device driver.
 */
#define IFACE_TX_CHAR( dev, c ) dev.iface.driver->tx.fchar( &dev, c )
#define IFACE_RX_CHAR( dev )    dev.iface.driver->rx.fchar( &dev )

#define pIFACE_TX_CHAR( dev, c ) dev->iface.driver->tx.fchar( &dev, c )
#define pIFACE_RX_CHAR( dev )    dev->iface.driver->rx.fchar( &dev )

/*
 * Call tx/rx block methods of device driver.
 */
#define IFACE_TX_BLOCK( dev, blk, size ) dev.iface.driver->tx.fblock( &dev, blk, size )
#define IFACE_TX_BLOCK( dev, blk, size ) dev.iface.driver->tx.fblock( &dev, blk, size )

#define pIFACE_TX_BLOCK( dev, blk, size ) dev->iface.driver->tx.fblock( &dev, blk, size )
#define pIFACE_TX_BLOCK( dev, blk, size ) dev->iface.driver->tx.fblock( &dev, blk, size )

#endif  /*  HAL_H_  */
