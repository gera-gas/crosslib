#define __ASM__
/**
 * @file     eabi.S
 * @brief    EABI initialization procedure.
 * @date     28.02.2009
 */
.file "eabi.S"

#include "config.h"
#include "gcc_macro_asm.h"
#include "ppc_regs.h"
#include "ppc_asm_helpers.h"

.section ".got2", "aw"
.align 2
/*
 * Address offset table with sections addresses.
 */
.LCTOC1 = .

/* Address of small data */
.lsdata = .-.LCTOC1
	.long  _SDA_BASE_

/* Address of small data2 */
.lsdata2 = .-.LCTOC1
	.long  _SDA2_BASE_


.section .text
/*
 * Initialize CPU EABI resources.
 */
GLOBAL( __eabi )

	llv		r11, .LCTOC1
	/*
	 * Load r13 with address of small data
	 * and load r2 with small data2.
	 */
	lwz		r13, .lsdata(r5)
	lwz		r2, .lsdata2(r5)

#if defined(__cplusplus) || defined(CPUINIT_CXX)
	/*
	 * Call Initialize functions (global constructors).
	 */
	b	__init
#endif
	blr


.section ".init", "ax"
/*
 * Call global C++ constructors.
 */
GLOBAL( __init )

	stwu		r1,  -8(r1)
	mflr		r0
	stw		r0,  12(r1)

	bl	__do_global_ctors_aux

	lwz		r0,  12(r1)
	mtlr		r0
	addi		r1,  r1,  8
	
	blr


.section ".fini", "ax"
/*
 * Call global C++ destructors.
 */
GLOBAL( __fini )

	stwu		1,  -8(r1)
	mflr		r0
	stw		r0,  12(r1)

	bl	__do_global_dtors_aux

	lwz		r0,  12(r1)
	mtlr		r0
	addi		r1,  r1,  8
	
	blr
