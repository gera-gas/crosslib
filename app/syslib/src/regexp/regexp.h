#ifndef REGEXP_H_
#define REGEXP_H_
/**
 *  @file     regexp.h
 *  @brief    Emplementation various regular expression.
 *  @author   Gerasimov A.S.
 */
#include <stdbool.h>

/**
 * Type describes simple filter rules for string.
 */
typedef struct fstring_st {
	/*
	 * Rules type.
	 */
	enum etype {
		FSTRING_TYPE_NONE,
		FSTRING_TYPE_BINCHAR,
		FSTRING_TYPE_DECCHAR,
		FSTRING_TYPE_HEXCHAR,
		FSTRING_TYPE_LETTERS,
		FSTRING_TYPE_CUSTOM
	} type;

	/*
	 * Point to custom string.
	 */
	const char *custom;

} fstring_t;

#ifdef __cplusplus
extern "C" {
#endif

bool fstring_match_chr ( const fstring_t *, char c );
bool fstring_match_str ( const fstring_t *, const char * );

#ifdef __cplusplus
}
#endif

#endif  /* REGEXP_H_ */
