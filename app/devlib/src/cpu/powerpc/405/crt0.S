#define __ASM__
/**
 * @file   boot.S
 * @brief  Startup program initialization procedure.
 * @date   28.02.2009
 */
.file "crt0.S"

#include "config.h"
#include "gcc_macro_asm.h"
#include "ppc_regs.h"
#include "ppc_asm_helpers.h"

.section ".got2", "aw"
.align 2
/*
 * Address offset table with sections addresses.
 */
.LCTOC1 = . + 32768

/* SBSS address range */
.lsbss_start = .-.LCTOC1
	.long  __sbss_start

.lsbss_end = .-.LCTOC1
	.long  __sbss_end

/* BSS address range */
.lbss_start = .-.LCTOC1
	.long  __bss_start

.lbss_end = .-.LCTOC1
	.long  __bss_start

/* Heap address range */
.lheap_start = .-.LCTOC1
	.long  _heap_start

.lheap_end = .-.LCTOC1
	.long  _heap_end

/* Stack address range */
.lstack_start = .-.LCTOC1 /* Hight address */
	.long  __stack

.lstack_end = .-.LCTOC1   /* Lower address */
	.long  _stack_end


.section .text
/*
 * Initialize program resources and jump to main.
 */
GLOBAL( _start )
	/*
	 * Initialize core.
	 */
	mfccr0		r0
	setbit		r0,  0x50000c00
	mtccr0		r0
	
	nilreg		r0
	llv		r5,  .LCTOC1
	/*
	 * Clear SBSS section.
	 */
	lwz		r6,  .lsbss_start(r5)
	lwz		r7,  .lsbss_end(r5)
	
	cmplw		r6,  r7
	beq	mk_clean_bss
	
	subf		r8,  r6,  r7
	srwi.		r9,  r8,  2
	beq		1f
	/*
	 * Clear by 32-bit word.
	 */
	addi		r6,  r6,  -4
	mtctr		r9
2:
	stwu		r0,  0x4(r6)
	bdnz	2b
	addi		r6,  r6,  4
	
	/*
	 * Clear by byte.
	 */
1:
	slwi		r9,  r9,  2
	subf.		r9,  r9,  r8
	beq	mk_clean_bss
	addi		r6,  r6,  -1
	mtctr		r9
2:
	stbu		r0,  0x1(r6)
	bdnz	2b


	/*
	 * Clear BSS section.
	 */
mk_clean_bss:

	lwz		r6,  .lbss_start(r5)
	lwz		r7,  .lbss_end(r5)
	
	cmplw		r6,  r7
	beq	mk_stack_point
	
	subf		r8,  r6,  r7
	srwi.		r9,  r8,  2
	beq		1f
	/*
	 * Clear by 32-bit word.
	 */
	addi		r6,  r6,  -4
	mtctr		r9
2:
	stwu		r0,  0x4(r6)
	bdnz	2b
	addi		r6,  r6,  4
	/*
	 * Clear by byte.
	 */
1:
	slwi		r9,  r9,  2
	subf.		r9,  r9,  r8
	beq	mk_stack_point
	addi		r6,  r6,  -1
	mtctr		r9
2:
	stbu		r0,  0x1(r6)
	bdnz	2b


mk_stack_point:
	/*
	 * Set stack and create first backnain frame.
	 */
	nilreg		r0
	lwz		r1,  .lstack_start(r5)
	stwu		r0,  -PPC_CTX_BACKCHAIN_SIZE(r1)
	/*
	 * Reset to zero of TBU,TBL registers.
	 */
	mtspr		0x11c, r0
	mtspr		0x11d, r0
	/*
	 * Jump to main.
	 */
	bl	main

#if defined(__cplusplus) || defined(CPUINIT_CXX)
	/*
	 * Call finalize functions (global desctructors).
	 */
	bl	__fini
#endif


/*
 * Program exit label.
 */
GLOBAL( _exit )
	
	halt
