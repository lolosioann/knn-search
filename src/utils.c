#include <stdlib.h>
#include <string.h>
#include "utils.h"

double_matrix_t *create_double_matrix(int rows, int cols) {

    double_matrix_t *matrix = malloc(sizeof(double_matrix_t));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (double **)malloc(rows * sizeof(double **));
    if (matrix->data == NULL) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (double *)malloc(cols * sizeof(double));
        if (matrix->data[i] == NULL) {
            // Free memory allocated so far
            for (int j = 0; j < i; j++) {
                free(matrix->data[j]);
            }
            return NULL;
        }
    }

    return matrix;
}

void free_double_matrix(double_matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

double *convert_to_1d(double_matrix_t *matrix) {
    double *data = (double *)malloc(matrix->rows * matrix->cols * sizeof(double));
    if (data == NULL) {
        return NULL;
    }

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            data[i * matrix->cols + j] = matrix->data[i][j];
        }
    }

    return data;
}

void quicksort(double *arr, int *idx, int n) {
    if (n < 2) {
        return;
    }

    double pivot = arr[n / 2];
    int i, j;
    for (i = 0, j = n - 1; ; i++, j--) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i >= j) {
            break;
        }
        swap_d(arr, i, j);
        swap_i(idx, i, j);
    }
    quicksort(arr, idx, i);
    quicksort(arr + i, idx + i, n - i);
}

void swap_d(double *arr, int i, int j) {
    double temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void swap_i(int *arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}