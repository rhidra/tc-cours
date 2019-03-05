/**
 * param.h
 *
 * Define some parameters used by the program.
 *
 * Author : Rémy Hidra
 *
 * 2018/2019
 */

#ifndef _PARAM_H_
#define _PARAM_H_

// Quantity of different combinations of bits in a byte
#define QUANTITY_OF_BYTES 256

// Quantity of bytes in the uncompressed data which will be encoded as a single symbol
// This parameter only works for value of 1
#define BYTES_PER_SYMBOL 1

// Quantity of different symbol possible
#define QUANTITY_OF_SYMBOLS QUANTITY_OF_BYTES * BYTES_PER_SYMBOL

// Buffer sizes
#define SIZE_BUFFER_HEADER 50000
#define SIZE_BUFFER 200

#endif
