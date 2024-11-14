#ifndef MAT_IO_H
#define MAT_IO_H

#include "/usr/local/MATLAB/R2024b/extern/include/matrix.h"  // MATLAB Matrix Library
#include "/usr/local/MATLAB/R2024b/extern/include/mat.h"
#include "utils.h"

/**
 * Function to read a matrix from a .mat file and store it in a C array.
 *
 * @param filename the name of the file to read from
 * @param variable the name of the variable in the .mat file
 * @return a pointer to the matrix if successful, NULL otherwise
 */
double_matrix_t *read_mat_file(const char* filename, const char* variable);

/**
 * Function to write the knn results to a .mat file.
 *
 * @param filename the name of the file to write to
 * @param idx the indices of the k-nearest neighbors
 * @param dst the distances of the k-nearest neighbors
 * @param query_n the number of query points
 * @param k the number of nearest neighbors
 * @return 0 if successful, 1 otherwise
 */
int write_mat_file(const char* filename, int* idx, double* dst, int query_n, int k);

#endif // MAT_READER_H