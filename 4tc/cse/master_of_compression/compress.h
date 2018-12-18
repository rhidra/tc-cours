/**
 * compress.h
 *
 * Define some useful structures and the function of the main program.
 *
 * Author : Rémy Hidra
 *
 * 2018/2019
 */

#ifndef _COMPRESS_H_
#define _COMPRESS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "heap.h"
#include "param.h"

// Store the output of the main program : the compressed or the uncompressed data
typedef struct {
    char *data;
    int size;
} OUTPUT;

// Store the header of a compressed file for the decompression
typedef struct {
    int size_symbols;
    char **symbols;
    int *freq;
    int unencoded_bits;
    int size_header;
} HEADER;

NODE* build_huffman_tree(char **data, int freq[], int size);
void build_codes(NODE *tree, char **symbols, char **symbols_code, int size_symbols);
int get_code(NODE *tree, char symbol[BYTES_PER_SYMBOL], char *bits, int n);
OUTPUT compress(char data[], int size);
int compress_data(char data[], int size, char **symbols, char **symbols_code, int size_symbols, int *compressed_data_bits);
void bits2bytes(char data_compressed[], int compressed_data_bits[], int size_compression);

OUTPUT decompress(char data[], int size);
HEADER parse_header(char data[], int size);
void bytes2bits(char data_compressed[], int compressed_data_bits[], int size_compression, int unencoded_bits);
int decompress_data(int *compressed_data_bits, int size_compressed_bits, char **symbols, char **symbols_code, int size_symbols, char *data_uncompressed, int tree_height);

void write_file(char *name, char *data, int size, int is_compressing);

#endif
