#ifndef _CC_CPP_H
#define _CC_CPP_H
/**
 *  @file     cc_cpp.h
 *  @brief    GCC C\C++ macros.
 *  @author   Gerasimov A.S.
 *  @date     2013-06-24
 */
#ifndef __ASM__

/*  ____________________________________________________________________________
 *
 *  ���������������� ���������������� ���������
 *  ��������� ����������� (__attribute__).
 *  ____________________________________________________________________________
 */

/**
 *  ������, ��������������� ������� GCC
 *  ��� ������������ �������� ������� �� ��������� 'x', 
 */
#define ALIGNED( x )     __attribute__((aligned(x)))

/**
 *  ����������� ������, �.�. ������� �����������, ���������� ������
 *  ���� � �����, ��� ������������.
 */
#define PACKED           __attribute__((packed))

/**
 *  ��������� ������ � ��������� ������ � ������ 'name'.
 */
#define SECTION( name )  __attribute__((section(name)))

/**
 *  ������������� �������� ������� "������ inline".
 */
#define INLINE  __inline__ __attribute__((always_inline))

/**
 *  ������� �� ����� ����������� �� ����������� inline.
 */
#define NOINLINE      __attribute__((noinline))

/**
 *  �������������� ��� �������, ��� ��� ����������
 *  � ������ ��������� �������� ����������.
 */
#define DEPRECATED    __attribute__((deprecated))

/**
 *  ���������� ������ �������, ���������� �� ����, ������� ��
 *  GCC ���������� ������ ������ �������.
 */
#define USED          __attribute__((__used__))

/**
 *  �������� �����������, ��� ��� ������� �� ����� ��������� (�.�. ���������� 
 *  ��� ��������� ������������� ���������� ������ ���������� �� ���������).
 */
#define CONST         __attribute__((__const__))

/**
 *  ���������� ���������� ������ ���������, ��� ������������ 
 *  �������� ������� ����������� � ����� ������.
 *  ���� �������������, ��� �����, ������ ���������� ������� ��������� ����� �����������.
 */
#define CHECKED       __attribute__((warn_unused_result))

/**
 *  ������ ������ ��������� ���� ��� ������������ �������.
 */
#define ALIAS( ... )  __attribute__ ((alias (__VA_ARGS__)))

/**
 *  ��������� �����������, ��� ������ ������� �������� ������������
 *  ����������, ��������������, ���������� ���������� �����������
 *  ������� �������� �� ������� � ��������� �������� �������� ABI.
 */
#define IRQ_HANDLER  __attribute__ ((interrupt_handler))
#define IRQ_FAST     __attribute__ ((fast_interrupt))


/*
 *  ____________________________________________________________________________
 *
 *  ��������� ����������� � �������� �������������
 *  ��������� ��� ��������� ������� ������������ ����.
 *  ____________________________________________________________________________
 *
 *  ���� ������� �������� "likely", �� ���������� ����� ��������� ������ ����
 *  True ��������������� ����� ���������. ��� ��� �������� False � ���� ������
 *  ����� �������� ����� ���������� ���������, ��� �� ��� ����������, �� � �����
 *  ��������. ��� ����� ������� ��� �������������� ��� �������� ���������� ��������.
 */

/**
 *  ����������� ��������� ���� ���
 *  ����o��� ��������� �����
 */
#define LIKELY( x )    __builtin_expect(!!(x), 1)

/**
 *  ����������� ��������� ���� ���
 *  �������� ��������� �����
 */
#define UNLIKELY( x )  __builtin_expect(!!(x), 0)


/*  ____________________________________________________________________________
 *
 *  ���������������� ���������������� ������������
 *  ��������� ����������� gcc.
 *  ____________________________________________________________________________
 */

/**
 *  ������ ��������� ������� ����������� ��� ������������� ����������.
 */
#define ASM  __asm__ __volatile__


/**
 *  ����������� ������� ���� � ��������� ��������� ('offset') ��
 *  ������� �������� ������� �� ��������� ���-�� ��������.
 */
#define p2align( offset )  ASM(".p2align "#offset"\n")


/**
 *  ��������� ��������� � ���������� ������ "n" ���
 *  ���������� GNU assembler.
 */
#define LINE_REPEAT( n, ... ) do {\
	ASM(".rep %0" :: "I"(n) );\
	__VA_ARGS__;\
	ASM(".endr");\
} while (0)

#endif  /*  __ASM__  */
#endif  /*  _CC_CPP_H  */
