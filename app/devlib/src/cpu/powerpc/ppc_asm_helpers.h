#ifndef PPC_ASM_HELPERS_H_
#define PPC_ASM_HELPERS_H_
/**
 *  @file     ppc_asm_helpers.h
 *  @brief    Helpers macros for assembler language.
 *  @date     29.10.2009
 */
#ifdef __ASM__

#define PPC_CTX_BACKCHAIN_SIZE  8
#define PPC_CTX_GPR_NUMB        31

/* Stack allocation for new data */
BEGINM( __STACK_ALLOC, num=0 )
    stwu  r1, - ((\num * 4) + PPC_CTX_BACKCHAIN_SIZE)(r1)
ENDM( )

/* Free stack frame */
BEGINM( __STACK_FREE, num=0 )
    addi  r1,  r1,  ((\num * 4) + PPC_CTX_BACKCHAIN_SIZE)
ENDM( )


/*
 * Recirsive save GPR value into stack.
 *
 * num -- GPR numbers.
 * reg -- first GPR.
 * off -- Start stack offset.
 */
BEGINM( __STACK_SAVE, num, reg, off )
    .if \num
        stw  \reg, \off(r1)
	    __STACK_SAVE  \num-1, \reg+1, \off+4
    .endif
ENDM( )

/*
 * Recirsive load GPR value from stack.
 *
 * num -- GPR numbers.
 * reg -- first GPR.
 * off -- Start stack offset.
 */
BEGINM( __STACK_LOAD, num, reg, off )
    .if \num
        lwz  \reg, \off(r1)
        __STACK_LOAD  \num-1, \reg+1, \off+4
    .endif
ENDM( )


/*
 * Various GPR save into stack start on <reg>.
 *
 * num  -- GPR number saved into stack.
 * numc -- Number of special registers saved into stack.
 * reg  -- First GPR.
 *
 * EXAMPLE:
    __CTX_SAVE_GPR  2, 0, r3
    //
    // Equivalent to
    //
    stw r1, -(16)(r1)
    stw r3, 0x8(r1)
    stw r4, 0xC(r1)
 * NOTE:
 * 1) r1 skip if <reg>=r0.
 * 2) <reg> default set on r0.
 */
BEGINM( __CTX_SAVE_GPR, num, numc, reg=0 )
    /*
     * Allocation size into stack for all registers.
     */
    __STACK_ALLOC (\num+\numc)
    /* GPR exists? */
    .if \num
        /* Save all GPR by SIMD instructions. */
        .if \num>=PPC_CTX_GPR_NUMB
            stw r0, (PPC_CTX_BACKCHAIN_SIZE)(r1)
            stmw r2, (PPC_CTX_BACKCHAIN_SIZE + 4)(r1)
        /* Save GPR part */
        .else
            /* r0 need save? */
            .if \reg==0
                stw  r0, (PPC_CTX_BACKCHAIN_SIZE)(r1)
	            /* Save other GPR */
                __STACK_SAVE \num-1, r2, 12
            .else
                .if (\reg+\num)>PPC_CTX_GPR_NUMB
                    stmw \reg, (PPC_CTX_BACKCHAIN_SIZE)(r1)
                .else
                    __STACK_SAVE \num, \reg, PPC_CTX_BACKCHAIN_SIZE
                .endif
            .endif
        .endif
    .endif
ENDM( )

/*
 * Work as __CTX_SAVE_GPR but only restore.
 */
BEGINM( __CTX_LOAD_GPR,  num, numc, reg=0 )
    /*
     * Allocation size into stack for all registers.
     */
    .if \num
        /* GPR exists? */
        .if \num>=PPC_CTX_GPR_NUMB
            lwz  r0,  (CTX_BACKCHAIN_SIZE)(r1)
            lmw  r2,  (CTX_BACKCHAIN_SIZE + 4)(r1)
        .else
            /* r0 need restore? */
            .if \reg==0
                lwz  r0,  (CTX_BACKCHAIN_SIZE)(r1)
                /* Restore other GPR */
                __STACK_LOAD \num-1, r2, 12
            .else
                .if (\reg+\num)>PPC_CTX_GPR_NUMB
                    lmw  \reg, (PPC_CTX_BACKCHAIN_SIZE)(r1)
                .else
                    __STACK_LOAD \num, \reg, PPC_CTX_BACKCHAIN_SIZE
                .endif
            .endif
        .endif
    .endif
    /*
     * Free stack frame.
     */
    __STACK_FREE (\num+\numc)
ENDM( )


/*
 * Save various numbers system registers.
 *
 * num  --  number of system registers.
 * nb   --  number already saved registres into frame.
 * sr1  --  name list of system registers (lr,msr,cr,...)
 */
BEGINM( __CTX_SAVE_SREGS, num, nb, sr1=0, sr2=0, sr3=0, sr4=0, sr5=0, sr6=0, sr7=0, sr8=0 )

    .if \num > 8
        .err
    .endif

    .if \num
        mf\sr1  r0
        stw  r0,  ( ((0+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
    .else
        .exitm
    .endif
    .if \num-1
        mf\sr2  r0
        stw  r0,  ( ((1+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
    .else
        .exitm
    .endif
    .if \num-2
        mf\sr3  r0
        stw  r0,  ( ((2+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
    .else
        .exitm
    .endif
    .if \num-3
        mf\sr4  r0
        stw  r0,  ( ((3+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
    .else
        .exitm
    .endif
    .if \num-4
        mf\sr5  r0
        stw  r0,  ( ((4+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
    .else
        .exitm
    .endif
    .if \num-5
        mf\sr6  r0
        stw  r0,  ( ((5+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
    .else
        .exitm
    .endif
    .if \num-6
        mf\sr7  r0
        stw  r0,  ( ((6+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
    .else
        .exitm
    .endif
    .if \num-7
        mf\sr8  r0
        stw  r0,  ( ((7+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
    .else
        .exitm
    .endif
ENDM( )

/*
 * Work as __CTX_SAVE_SREGS but only restore.
 */
BEGINM( __CTX_LOAD_SREGS,  num, nb, sr1=0, sr2=0, sr3=0, sr4=0, sr5=0, sr6=0, sr7=0, sr8=0 )

    .if \num > 8
        .err
    .endif

    .if \num
        lwz  r0,  ( ((0+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
        mt\sr1  r0
    .else
        .exitm
    .endif
    .if \num-1
        lwz  r0,  ( ((1+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
        mt\sr2  r0
    .else
        .exitm
    .endif
    .if \num-2
        lwz  r0,  ( ((2+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
        mt\sr3  r0
    .else
        .exitm
    .endif
    .if \num-3
        lwz  r0,  ( ((3+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
        mt\sr4  r0
    .else
        .exitm
    .endif
    .if \num-4
        lwz  r0,  ( ((4+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
        mt\sr5  r0
    .else
        .exitm
    .endif
    .if \num-5
        lwz  r0,  ( ((5+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
        mt\sr6  r0
    .else
        .exitm
    .endif
    .if \num-6
        lwz  r0,  ( ((6+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
        mt\sr7  r0
    .else
        .exitm
    .endif
    .if \num-7
        lwz  r0,  ( ((7+\nb) * 4)+CTX_BACKCHAIN_SIZE )(r1)
        mt\sr8  r0
    .else
        .exitm
    .endif
ENDM( )


/*
 *  Save various CPU context.
 *
 *  gpr_base  --  First GPR.
 *  gpr_num   --  GPR numbers.
 *  sprg_num  --  numbers of system registers.
 *  ...       --  name list of system registers (lr,msr,cr,...)
 *
 * EXAMPLE:
    //Save all CPU context.
    CTX_SAVE(
        // GPR save.
        r0, 31,
        // save system registers.
        7, lr, cr, ctr, xer, srr2, srr3, usprg0 )

    bl <Some handler>

    //Restore all CPU context.
    CTX_LOAD(
        // GPR restore.
        r0, 31,
        // restore system registers.
        7, lr, cr, ctr, xer, srr2, srr3, usprg0 )
 */
#define CTX_SAVE( gpr_base, gpr_num, sprg_num, ... )\
	__CTX_SAVE_GPR\
		gpr_num,\
		sprg_num,\
		gpr_base\
	;\
	__CTX_SAVE_SREGS\
		sprg_num,\
		gpr_num,\
		__VA_ARGS__
/*
 * Work as CTX_SAVE but only restore.
 */
#define CTX_LOAD( gpr_base, gpr_num, sprg_num, ... )\
	__CTX_LOAD_SREGS\
		sprg_num,\
		gpr_num,\
		__VA_ARGS__\
	;\
	__CTX_LOAD_GPR\
		gpr_num,\
		sprg_num,\
		gpr_base


/*
 * Load label address into GPR.
 * rn  -- GPR
 * val -- label name.
 */
BEGINM( llv,  rn, val )
  lis  \rn, \val@h
  ori  \rn, \rn, \val@l
ENDM( )


/*
 * Load constant into GPR.
 * rn  -- GPR
 * val -- label name.
 */
BEGINM( llc,  rn, constant )
  .if \constant>0x7FFF
    lis  \rn, \constant@h
    .if (\constant&0xFFFF)>0
      ori  \rn, \rn, \constant@l
    .endif
  .else
    li  \rn, \constant
  .endif
ENDM( )


/*
 * Halt CPU.
 */ 
BEGINM( halt )
	b  .
ENDM( )


/*
 * Clear GPR.
 */
BEGINM( nilreg, gpr )
	xor  \gpr, \gpr, \gpr
ENDM( )


/*
 * Set bit into GPR by OR operation.
 */
BEGINM( setbit, gpr, bits )
  .if \bits>0x7FFF
    oris  \gpr, \gpr, \bits@h
  .endif
  .if (\bits&0xFFFF)>0
    ori  \gpr, \gpr, \bits@l
  .endif
ENDM( )


/*
 *  Move value between GPR:
 *
 *  MR( r10, r3, 2 ) == r3->r10, and then r4->r11.
 */
#define MR( dst_gpr, src_gpr, ... )\
	__MOVR  dst_gpr, src_gpr, __VA_ARGS__

BEGINM( __MOVR,  dst, src, num=0 )
    .if \num
        mr  \dst, \src
        __MOVR  \dst+1, \src+1, \num-1
    .endif
ENDM( )

#endif /*  __ASM__  */
#endif /*  PPC_ASM_HELPERS_H_  */
