/**
 * sort.h
 *
 * Define the structure RESULT, useful to print the results data in a file.
 * Define the function of the program.
 *
 * Author : Rémy Hidra
 *
 * 2018/2019
 */

#ifndef SORT_H_
#define SORT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define SIZE_BUFFER 20
#define SWAP(a, b) { int tmp; tmp = a; a = b; b = tmp; }

// Size limit before using the merge sort algorithm in the introsort algorithm
#define INTROSORT_SIZE_THRESHOLD 16

typedef struct {
    char *input_file;
    int algo_index;
    int input_size;
    double run_time;
    int *sorted_list;
} RESULT;

void print_results(RESULT);

void insertion_sort(int seq[], int left, int right);

void quick_sort(int seq[], int left, int right);
int qs_partition(int seq[], int left, int right);

void merge_sort(int seq[], int left, int right, int size);
void ms_merge(int seq[], int left, int middle, int right, int size);

void intro_sort(int seq[], int size);
void introsort_loop(int seq[], int left, int right, int size, int depth_limit);

#endif
