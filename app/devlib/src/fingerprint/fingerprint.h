#ifndef FINGERPRINT_H_
#define FINGERPRINT_H_
/**
 * @file     fingerprint.h
 * @brief    Driver for Z70 optical fingerprint sanner.
 * @author   Gerasimov A.S.
 * @note
 * Header dependencies:
 *
 * #include "io.h"
 */
typedef struct fingerprint_st {
	ioctx_t *ioctx;
	/*
	 * Fingerprint functions API.
	 */
} fingerprint_t;

#endif  /* FINGERPRINT_H_ */
