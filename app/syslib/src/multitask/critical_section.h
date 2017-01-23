#ifndef CRITICAL_SECTION_H_
#define CRITICAL_SECTION_H_
/**
 *  @file     critical_section.h
 *  @brief    Critical section methods.
 *  @author   Gerasimov A.S.
 *  @date     2014-09-08 10:54:18
 */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct critical_section_st {
    fptr_t entry;
    fptr_t leave;
} critical_section_t;

extern critical_section_t critical_section;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Placed code into critical section.
 */
#define CRITICAL_SECTION( ... )\
({\
	critical_section.entry( );\
	__VA_ARGS__;\
	critical_section.leave( );\
});

#endif  /*  CRITICAL_SECTION_H_  */
