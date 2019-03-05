#ifndef MSS_H_
#define MSS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE_BUFFER 20

typedef struct {
    char *input_file;
    int algo_index;
    int input_size;
    int left;
    int right;
    int sum;
    double run_time;
} RESULT;

RESULT mss_squared(const int[], int);
RESULT mss_nlogn(const int[], int, int);
RESULT mss_linear(const int[], int);
void print_results(RESULT);

#endif
