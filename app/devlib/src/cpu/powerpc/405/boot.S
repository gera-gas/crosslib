#define __ASM__
/**
 * @file    boot.S
 * @brief   PowerPC startup functions.
 * @date    28.02.2009
 */
.file "boot.S"

#include "gcc_macro_asm.h"
#include "ppc_regs.h"
#include "ppc_asm_helpers.h"


.section .boot0, "ax"
/*
 * Jump to start by absolute address.
 *
 * NOTE:
 * Address space between <boot> and <boot0>
 * must be no more then 0x3fffff (24 bit).
 */
GLOBAL( _boot0 )

	llv	r0,  _start
	mtlr	r0
	blr


.section .boot, "ax"
/*
 * CPU reset entry point.
 *
 * NOTE:
 * Must be allocated to 0xfffffffc.
 */
GLOBAL( _boot )
	
	b  _boot0
