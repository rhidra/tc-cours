/**
 * sort.c
 *
 * Sorts an array given in a file as parameter.
 * Usage: ./mp2_20180326 <file> <algo_index>
 * The file format must be :
 * <size> <number_1> <number_2> <number_3> ... <number_size>
 *
 * The <algo_index> corresponds to the sorting algorithm to use.
 * There are 4 possible values :
 * - 1 : Insertion sort O(n²)
 * - 2 : Quick sort O(n²)
 * - 3 : Merge sort O(n*log(n))
 * - 4 : Introsort (Quick sort + Merge sort + Insertion sort)
 *
 * Author : Rémy Hidra
 *
 * 2018/2019
 */

#include "sort.h"

int main(int argc, char **argv) {
    // Arguments parsing
    if (argc != 3) {
        printf("Usage: ./mp2_20180326 <file> <algo_index>");
        exit(1);
    }

    int algo_index = atoi(argv[2]);
    printf("Algo #%d\n", algo_index);

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File does not exist !\n");
        exit(1);
    }

    // File parsing
    char c;
    char buf[SIZE_BUFFER];
    int ibuf = 0, iseq = 0, i, *seq, size;

    while ((c = fgetc(file)) != ' ') {
        buf[ibuf++] = c;
    }
    buf[ibuf] = '\0';
    size = atoi(buf);
    seq = malloc(size * sizeof(int));
    ibuf = 0;
    for (i = 0; i < SIZE_BUFFER; i++)
        buf[i] = '\0';

    while ((c = fgetc(file)) != EOF) {
        if (c != ' ' && c != '\n') {
            buf[ibuf] = c;
            ibuf++;
        } else {
            seq[iseq] = atoi(buf);
            iseq++;
            ibuf = 0;
            for (i = 0; i < SIZE_BUFFER; i++)
            buf[i] = '\0';
        }
    }
    fclose(file);

    // Display the input list
    // printf("List : ");
    // for (i = 0; i < size; i++) {
    //     printf("%d ", seq[i]);
    // }
    // printf("\n");

    // Sorting
    RESULT result;
    clock_t start_time, end_time;
    start_time = clock();
    switch (algo_index) {
        case 1:
        insertion_sort(seq, 0, size-1);
        break;
        case 2:
        quick_sort(seq, 0, size-1);
        break;
        case 3:
        merge_sort(seq, 0, size-1, size);
        break;
        case 4:
        intro_sort(seq, size);
        break;
        default:
        printf("Error in algorithm index !\n");
        exit(1);
        break;
    }
    end_time = clock();

    // End of the sorting
    // Display the results
    result.algo_index = algo_index;
    result.input_size = size;
    result.input_file = argv[1];
    result.run_time = (double)(end_time - start_time) * 1000 / CLOCKS_PER_SEC;
    result.sorted_list = seq;

    print_results(result);

    // Free memory allocation
    free(seq);

    return 0;
}

/**
 * insertion_sort()
 * Sort the array using the insertion sort algorithm iteratively.
 * The time complexity of the algorithm is O(n²).
 * Take the beginning and the end of the array index.
 */
void insertion_sort(int seq[], int left, int right) {
    int i, j, tmp;

    for (i = left; i <= right; i++) {
        tmp = seq[i];
        j = i;
        while ((j > 0) && (tmp < seq[j-1])) {
            seq[j] = seq[j-1];
            j--;
        }
        seq[j] = tmp;
    }
}

/**
 * quick_sort()
 * Sort the array using the quick sort algorithm recursively.
 * The time complexity of the algorithm is O(n²), but the
 * average time complexity is O(n*log(n)).
 * Take the beginning and the end of the array index.
 */
void quick_sort(int seq[], int left, int right) {
    int pivot;

    if (right - left > 0) {
        pivot = qs_partition(seq, left, right);

        quick_sort(seq, left, pivot - 1);
        quick_sort(seq, pivot + 1, right);
    }
}

int qs_partition(int seq[], int left, int right) {
    int i, pivot;

    pivot = left;
    for (i = left; i < right; i++) {
        if (seq[i] < seq[right]) {
            SWAP(seq[i], seq[pivot]);
            pivot++;
        }
    }
    SWAP(seq[right], seq[pivot]);
    return pivot;
}

/**
 * merge_sort()
 * Sort the array using the merge sort algorithm recursively.
 * The time complexity of the algorithm is O(n*log(n)).
 * Take the beginning and the end of the array index, and the total size of
 * the array, for memory allocation purpose.
 */
void merge_sort(int seq[], int left, int right, int size) {
    int middle;

    if (left < right) {
        middle = (left + right)/2;
        merge_sort(seq, left, middle, size);
        merge_sort(seq, middle + 1, right, size);
        ms_merge(seq, left, middle, right, size);
    }
}

void ms_merge(int seq[], int left, int middle, int right, int size) {
    int i, i_left, i_right, *buffer;
    buffer = malloc(sizeof(int)*size);

    memcpy(buffer + left, seq + left, sizeof(int)*(right - left + 1));

    i_left = left;
    i_right = middle + 1;
    i = left;

    while ((i_left <= middle) && (i_right <= right)) {
        if (buffer[i_left] < buffer[i_right]) {
            seq[i++] = buffer[i_left++];
        } else {
            seq[i++] = buffer[i_right++];
        }
    }

    while (i_left <= middle) {
        seq[i++] = buffer[i_left++];
    }
    while (i_right <= right) {
        seq[i++] = buffer[i_right++];
    }

    free(buffer);
}

/**
 * intro_sort()
 * Sort the array using the introsort algorithm recursively.
 * Uses a mix of the quick sort algorithm, the insertion sort and
 * the merge sort algorithm.
 * Take the total size of the array as input.
 */
void intro_sort(int seq[], int size) {
    introsort_loop(seq, 0, size-1, size, 2*log(size));
}

void introsort_loop(int seq[], int left, int right, int size, int depth_limit) {
    int pivot;

    if (right - left > INTROSORT_SIZE_THRESHOLD) {
        if (depth_limit == 0) {
            merge_sort(seq, left, right, size);
        } else {
            depth_limit--;
            pivot = qs_partition(seq, left, right);
            introsort_loop(seq, left, pivot-1, size, depth_limit);
            introsort_loop(seq, pivot+1, right, size, depth_limit);
            right = pivot;
        }
    } else {
        insertion_sort(seq, left, right);
    }
}

/**
 * print_results()
 * Print a RESULT struct in a file.
 */
void print_results(RESULT result) {
    char output_name[109];
    int i;
    for (i = 0; i < 109; i++)
        output_name[i] = '\0';
    sprintf(output_name, "result_%d_", result.algo_index);
    strcat(output_name, result.input_file);
    // printf("Input file : %s\n", result.input_file);
    // printf("Output file : %s\n", output_name);
    // printf("Algo index : %d\n", result.algo_index);
    // printf("Input size : %d\n", result.input_size);
    // printf("Running time : %f\n", result.run_time);
    // printf("List : ");
    // for (i = 0; i < result.input_size; i++)
    //     printf("%d ", result.sorted_list[i]);
    // printf("\n");

    FILE *file = fopen(output_name, "w");
    fprintf(file, "%s\n", result.input_file);
    fprintf(file, "%d\n", result.algo_index);
    fprintf(file, "%d\n", result.input_size);
    fprintf(file, "%f\n", result.run_time);
    for (i = 0; i < result.input_size; i++)
        fprintf(file, "%d ", result.sorted_list[i]);
    fclose(file);
}
