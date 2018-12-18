/**
 * heap.h
 *
 * Utility functions to manipulate a min heap.
 * The Huffman tree is built using a min heap.
 *
 * Author : Rémy Hidra
 *
 * 2018/2019
 */

#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "param.h"

// Element of the tree
typedef struct _node {
    char symbol[BYTES_PER_SYMBOL];
    int freq;
    struct _node *left;
    struct _node *right;
} NODE;

// Main structure used for conveniently store the heap and build the tree
typedef struct {
    int size; // Size of the heap (size of the array **nodes)
    int capacity; // Maximum value for size
    NODE **nodes;
} HEAP;

// Utility macros
#define SWAP(a, b) { NODE *tmp; tmp = *a; *a = *b; *b = tmp; }
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

NODE* new_node(char symbol[BYTES_PER_SYMBOL], int freq);
HEAP* init_heap(char **data, int freq[], int size);
void heapify(HEAP *heap, int idx);
NODE* extract(HEAP *heap);
void insert(HEAP *heap, NODE *node);
int height_tree(NODE *tree);
void free_tree(NODE *tree);

#endif
