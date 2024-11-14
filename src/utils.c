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