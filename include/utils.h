#ifndef UTILS_H
#define UTILS_H

// Structure to represent a matrix of doubles
typedef struct double_matrix_t {
    double **data;  // Pointer to the matrix data
    int rows;       // Number of rows in the matrix
    int cols;       // Number of columns in the matrix
} double_matrix_t;

/**
 * This function takes two integer parameters m, n and returns an empty m x n matrix.
 *
 * @param a The rows of the matrix.
 * @param b The columns of the matrix.
 * @return A pointer to the matrix if successful, NULL otherwise.
 */
double_matrix_t *create_double_matrix(int rows, int cols);

/**
 * This function frees the memory allocated for a double matrix.
 *
 * @param matrix The matrix to be freed.
 */
void free_double_matrix(double_matrix_t *matrix);

/**
 * This function reduces a 2D array to a 1D array.
 *
 * @param matrix The matrix to be reduced.
 * @return A double array containing the data from theoriginal matrix in row major format.
 */
double *convert_to_1d(double_matrix_t *matrix);

void swap_d(double *arr, int i, int j);
void swap_i(int *arr, int i, int j);
void quicksort(double *arr, int *idx, int n);
#endif  // UTILS_H