/**
 * @file     vt100_rcv.c
 * @brief    VT-100 receive functions.
 * @author   Gerasimov A.S.
 * @date     08.11.2012
 * @note     Implemented by PT.
 */
#include "hal/hal.h"
#include "multitask/thread.h"
#include "buffer/buffer.h"
#include "proto/vt100/vt100_esc.h"
#include "proto/vt100/vt100.h"


static PT_STATE( vt100_rcv_state_0 );
static PT_STATE( vt100_rcv_state_1 );
/**
 * @brief
 * Receive message at VT-100 protocol format.
 *
 * @param argin  : [in] used as in/out parameter for context.
 * @param argout : [out] not use.
 */
PT_CREATE( pt_vt100, PT_FLAG_NONE,
	vt100_rcv_state_0,
	vt100_rcv_state_1 );


/**
 * @brief
 * vt100_rcv state-0.
 * Execution all startup verifications.
 */
static PT_STATE( vt100_rcv_state_0 )
{
	vt100_ctx_t *ctx = (vt100_ctx_t *)argin;

	/*
	 * Check on exist char in RX.
	 */
	if( !IFACE_RX_READY( ctx->io_device ) )
	{
		return PT_HOLD;
	}

	ctx->count++;
	/*
	 * Check length of received bytes.
	 * If buffer overflowed, reset to begin.
	 */
	if( ctx->count >= ctx->io_buffer->size )
	{
		ctx->count = 0;

		return PT_HOLD;
	}

	return PT_NEXT;
}


/**
 * @brief
 * vt100_rcv state-1.
 * Analysis received byte.
 */
static PT_STATE( vt100_rcv_state_1 )
{
	vt100_ctx_t *ctx = (vt100_ctx_t *)argin;

	/*
	 * Read char from device RX buffer.
	 */
	uint8 c = IFACE_RX_CHAR( ctx->io_device );


	uint8 *pbuffer = ctx->io_buffer->addr;
	size_t cnt     = ctx->count;
	/*
	 * Save char to context buffer.
	 */
	pbuffer[ cnt - 1 ] = c;

	/*
	 * Analysis received char on
	 * final condition of message.
	 */
	if( cnt == 1 )
	{
		if( c != 0x1B )
		{
			return PT_NEXT;
		}
	}
	else if( cnt == 2 )
	{
		if( c != 0x5B )
		{
			return PT_NEXT;
		}
	}
	else
	{
		if( (c - 0x40) <= (0x7E - 0x40) )
		{
			return PT_NEXT;
		}
	}

	return PT_BACK;
}
