/**
 * @file     vt100_snd.c
 * @brief    VT-100 send functions.
 * @author   Gerasimov A.S.
 * @date     08.11.2012
 * @note     Implemented by PT.
 */
#include "string/string.h"
#include "hal/hal.h"
#include "multitask/thread.h"
#include "buffer/buffer.h"
#include "proto/vt100/vt100_esc.h"
#include "proto/vt100/vt100.h"

static PT_STATE( vt100_snd_state_init );
static PT_STATE( vt100_snd_state_tx_ready );
static PT_STATE( vt100_snd_state_snd_esc );
static PT_STATE( vt100_snd_state_snd_param );
static PT_STATE( vt100_snd_state_snd_cmd );
/**
 * @brief
 * Send message at VT-100 protocol format.
 *
 * @param argin  : [in] used as in/out parameter for context.
 * @param argout : [out] not use.
 *
 * @example
 *
 * char bufmem[ 40 ];
 *
 * buffer_t buffer = {
 * 	.addr = bufmem,
 * 	.size = sizeof( bufmem )
 * };
 * 
 * vt100_ctx_t vt100_ctx = {
 * 	.io_device = &<device>,
 * 	.io_buffer = &buffer,
 * 	.count = 0
 * };
 *
 * vt100_ctx.io_buffer->addr = "123";
 * vt100_ctx.io_param = "AB";
 * //
 * // Send VT-100 message from vt100_ctx.io_buffer (bufmem)
 * //
 * PT_WAIT( vt100_snd, &vt100_ctx, NULL );
 */
PT_CREATE( vt100_snd, PT_FLAG_NONE,
	/* 0 */ vt100_snd_state_init,
	/* 1 */ vt100_snd_state_tx_ready,
	/* 2 */ vt100_snd_state_snd_esc,
	/* 3 */ vt100_snd_state_tx_ready,
	/* 4 */ vt100_snd_state_snd_param,
	/* 5 */ vt100_snd_state_tx_ready,
	/* 6 */ vt100_snd_state_snd_cmd );


/**
 * @brief
 * Initialize VT-100 SND state machine.
 */
static PT_STATE( vt100_snd_state_init )
{
	vt100_ctx_t *ctx = (vt100_ctx_t *)argin;

	ctx->count = 0;

	if( !ctx->io_device )
	{
		return PT_RESET;
	}

	return PT_NEXT;
}


/**
 * @brief
 * Check TX ready to send.
 */
static PT_STATE( vt100_snd_state_tx_ready )
{
	vt100_ctx_t *ctx = (vt100_ctx_t *)argin;

	/*
	 * Check on exist char in RX.
	 */
	if( !IFACE_TX_READY( ctx->io_device ) )
	{
		return PT_HOLD;
	}

	return PT_NEXT;
}


/**
 * @brief
 * Send char from ESC string.
 */
static PT_STATE( vt100_snd_state_snd_esc )
{
	vt100_ctx_t *ctx = (vt100_ctx_t *)argin;

	uint8 *esc = ctx->io_buffer->addr;
	/*
	 * Send char from ESC string except last char (command).
	 */
	if( esc[ ctx->count + 1 ] == '\0' )
	{
		ctx->count = 0;
		/*
		 * Check parameters on exist.
		 * If parameters apsent, jump to command sending.
		 */
		if( !ctx->io_param )
		{
			return PT_JUMP( 3 );
		}
		return PT_NEXT;
	}

	IFACE_TX_CHAR( ctx->io_device, esc[ ctx->count++ ] );

	return PT_BACK;
}

/* Here tx_ready called */

/**
 * @brief
 * Send additional parameters.
 */
static PT_STATE( vt100_snd_state_snd_param )
{
	vt100_ctx_t *ctx = (vt100_ctx_t *)argin;

	/*
	 * If parameters is not exist, skip this state.
	 */
	if( ctx->io_param[ ctx->count ] == '\0' )
	{
		return PT_NEXT;
	}

	IFACE_TX_CHAR( ctx->io_device, ctx->io_param[ ctx->count++ ] );

	return PT_BACK;
}

/* Here tx_ready called */

/**
 * @brief
 * Send ESC command char.
 */
static PT_STATE( vt100_snd_state_snd_cmd )
{
	vt100_ctx_t *ctx = (vt100_ctx_t *)argin;

	uint8 *esc = ctx->io_buffer->addr;
	/*
	 * Get offset of last char in ESC string.
	 */
	size_t cmd = strlen( esc ) - 1;

	IFACE_TX_CHAR( ctx->io_device, esc[ cmd ] );

	return PT_NEXT;
}
