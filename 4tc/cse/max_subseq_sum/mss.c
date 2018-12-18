#include "mss.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: ./mss20180326 <file> <algo_index>");
        exit(1);
    }

    int algo_index = atoi(argv[2]);
    printf("Algo #%d\n", algo_index);

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File does not exist !\n");
        exit(1);
    }

    char c;
    char buf[SIZE_BUFFER];
    int ibuf = 0, iseq = 0, i, *seq, size;

    while ((c = fgetc(file)) != ' ') {
        buf[ibuf] = c;
        ibuf++;
    }
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
/*
    printf("List : ");
    for (i = 0; i < size; i++) {
        printf("%d ", seq[i]);
    }
    printf("\n");
*/
    RESULT result;
    clock_t start_time, end_time;
    start_time = clock();
    switch (algo_index) {
        case 1:
        result = mss_squared(seq, size);
        break;
        case 2:
        result = mss_nlogn(seq, 0, size-1);
        break;
        case 3:
        result = mss_linear(seq, size);
        break;
        default:
        printf("Error in algorithm index !\n");
        exit(1);
        break;
    }
    end_time = clock();

    result.algo_index = algo_index;
    result.input_size = size;
    result.input_file = argv[1];
    result.run_time = (double)(end_time - start_time) * 1000 / CLOCKS_PER_SEC;

    print_results(result);

    free(seq);

    return 0;
}

RESULT mss_squared(const int seq[], int size) {
    int this_sum, i, j;
    RESULT result;
    result.sum = -30000;

    for (i = 0; i < size; i++) {
        this_sum = 0;
        for (j = i; j < size; j++) {
            this_sum += seq[j];
            if (this_sum > result.sum) {
                result.sum = this_sum;
                result.left = i;
                result.right = j;
            }
        }
    }

    return result;
}

RESULT mss_nlogn(const int seq[], int left, int right) {
    int left_border_sum, right_border_sum;
    int center, i;
    RESULT r_left, r_right, r_left_border, r_right_border;


    if (left == right) {
        r_left.sum = seq[left];
        r_left.left = left;
        r_left.right = right;
        return r_left;
    }

    center = (left + right) / 2;
    r_left = mss_nlogn(seq, left, center);
    r_right = mss_nlogn(seq, center+1, right);

    r_left_border.sum = -30000;
    r_left_border.left = center;
    left_border_sum = 0;
    for (i = center; i >= left; i--) {
        left_border_sum += seq[i];
        if (left_border_sum >= r_left_border.sum) {
            r_left_border.sum = left_border_sum;
            r_left_border.left = i;
        }
    }

    r_right_border.sum = -30000;
    right_border_sum = 0;
    for (i = center + 1; i <= right; i++) {
        right_border_sum += seq[i];
        if (right_border_sum > r_right_border.sum) {
            r_right_border.sum = right_border_sum;
            r_right_border.right = i;
        }
    }
    r_left_border.sum += r_right_border.sum;
    r_left_border.right = r_right_border.right;

    if (r_left.sum >= r_right.sum) {
        if (r_left.sum >= r_left_border.sum) {
            return r_left;
        } else {
            return r_left_border;
        }
    } else if (r_right.sum > r_left_border.sum) {
        return r_right;
    } else {
        return r_left_border;
    }
}

RESULT mss_linear(const int seq[], int size) {
    int sum = 0, i, l = 0;
    int max_negative = -30000, i_negative = 0, is_all_negative = 1;
    RESULT result;
    result.sum = 0;
    result.left = 0;
    result.right = size-1;

    for (i = 0; i < size; i++) {
        sum += seq[i];

        if (sum > result.sum) {
            result.sum = sum;
            result.right = i;
            result.left = l;
            is_all_negative = 0;
        } else if (sum < 0) {
            if (is_all_negative && seq[i] > max_negative) {
                max_negative = seq[i];
                i_negative = i;
            }
            sum = 0;
            l = i + 1;
        }
    }

    if (is_all_negative) {
        result.sum = max_negative;
        result.left = i_negative;
        result.right = i_negative;
        return result;
    } else {
        result.sum = result.sum;
        return result;
    }
}

void print_results(RESULT result) {
    char output_name[107];
    int i;
    for (i = 0; i < 107; i++)
        output_name[i] = '\0';
    strcat(output_name, "result_");
    strcat(output_name, result.input_file);
    FILE *file = fopen(output_name, "w");
    fprintf(file, "%s\n", result.input_file);
    /*printf("Input file : %s\n", result.input_file);
    printf("Algo index : %d\n", result.algo_index);
    printf("Input size : %d\n", result.input_size);
    printf("Left : %d\n", result.left);
    printf("Right : %d\n", result.right);
    printf("Sum : %d\n", result.sum);*/
    printf("Running time : %f\n", result.run_time);
    fprintf(file, "%d\n", result.algo_index);
    fprintf(file, "%d\n", result.input_size);
    fprintf(file, "%d\n", result.left);
    fprintf(file, "%d\n", result.right);
    fprintf(file, "%d\n", result.sum);
    fprintf(file, "%f", result.run_time);
    fclose(file);
}
