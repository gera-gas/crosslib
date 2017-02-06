#ifndef REGEXP_H_
#define REGEXP_H_
/**
 *  @file     regexp.h
 *  @brief    Emplementation various regular expression.
 *  @author   Gerasimov A.S.
 */
#include <stdbool.h>

/**
 * Type describes simple string regular expression.
 */
typedef struct regexp_sz_st {
	/*
	 * Data template type.
	 */
	enum etype {
		REGEXP_TYPE_BINCHAR,
		REGEXP_TYPE_DECCHAR,
		REGEXP_TYPE_HEXCHAR,
		REGEXP_TYPE_LETTERS,
		REGEXP_TYPE_CUSTOM
	} type;

	/*
	 * Point to custom string.
	 */
	const char *custom;

} regexp_sz_t;

#ifdef __cplusplus
extern "C" {
#endif

bool regexp_match_szc ( const regexp_sz_t *, char c );
bool regexp_match_szs ( const regexp_sz_t *, const char * );

#ifdef __cplusplus
}
#endif

#endif  /* REGEXP_H_ */
