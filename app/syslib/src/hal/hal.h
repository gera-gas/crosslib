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
 * Type describe hardware device.
 */
typedef struct device_st {
	struct device_st *next;

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
 * dev -- point to address of device_t object.
 */
#define IFACE_INIT( dev ) ((device_t *)(dev))->iface.driver->init.f( ((device_t *)(dev)) )
#define IFACE_FINI( dev ) ((device_t *)(dev))->iface.driver->fini.f( ((device_t *)(dev)) )

/*
 * Call <cmd> methods of device driver.
 * dev -- point to address of device_t object.
 */
#define IFACE_CMD( dev, cmd, par ) ((device_t *)(dev))->iface.driver->cmd.f( ((device_t *)(dev)), cmd, par )

/*
 * Call tx/rx ready methods of device driver.
 * dev -- point to address of device_t object.
 */
#define IFACE_TX_READY( dev ) ((device_t *)(dev))->iface.driver->tx_ready.f( ((device_t *)(dev)) )
#define IFACE_RX_READY( dev ) ((device_t *)(dev))->iface.driver->rx_ready.f( ((device_t *)(dev)) )

/*
 * Call tx/rx char methods of device driver.
 * dev -- point to address of device_t object.
 */
#define IFACE_TX_CHAR( dev, c ) ((device_t *)(dev))->iface.driver->tx.fchar( ((device_t *)(dev)), c )
#define IFACE_RX_CHAR( dev )    ((device_t *)(dev))->iface.driver->rx.fchar( ((device_t *)(dev)) )

/*
 * Call tx/rx block methods of device driver.
 * dev -- point to address of device_t object.
 */
#define IFACE_TX_BLOCK( dev, blk, size ) ((device_t *)(dev))->iface.driver->tx.fblock( ((device_t *)(dev)), blk, size )
#define IFACE_TX_BLOCK( dev, blk, size ) ((device_t *)(dev))->iface.driver->tx.fblock( ((device_t *)(dev)), blk, size )

#endif  /*  HAL_H_  */
