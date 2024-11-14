#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "knn.h"
#include "mat_io.h"

int main(int argc, char** argv)
{

    // Check for correct number of arguments
    if (argc != 6)
    {
        fprintf(stderr, "Usage: %s <input_file> <corpus variable> <query variable> <output_file> <no. of neighbors>\n", argv[0]);
        return -1;
    }

    // convert k to integer
    char *p;
    int k;
    errno = 0;

    long conv = strtol(argv[5], &p, 10);

    // Check for errors during conversion
    if (errno == ERANGE)
    {
        fprintf(stderr, "Error: Integer out of range.\n");
        return 1;
    }
    else if (*p != '\0')
    {
        fprintf(stderr, "Error: Non-numeric characters detected.\n");
        return 1;
    }
    else if (conv > INT_MAX || conv < 0) {
        fprintf(stderr, "Error: Integer exceeds 'int' range.\n");
        return 1;
    }
    else
    {
        // Successful conversion
        k = (int)conv;
    }
    // check if output file is a .mat file
    char *ext = "";
    char *dot = strrchr(argv[4], '.');
    if (dot && dot != argv[4]) {
        ext = dot + 1;
    }
    if (strcmp(ext, "mat") != 0) {
        fprintf(stderr, "Error: Output file must be a .mat file\n");
        return -1;
    }

    // Read data from a .mat file
    double_matrix_t *corpus = read_mat_file(argv[1], argv[2]);
    if (corpus == NULL) {
        fprintf(stderr, "Failed to read Corpus .mat file\n");
        return -1;
    }

    double_matrix_t *query = read_mat_file(argv[1], argv[3]);
    if (query == NULL) {
        fprintf(stderr, "Failed to read Query .mat file\n");
        return -1;
    }

    // Allocate memory for k-nearest neighbor results
    int *idx = malloc(query->rows * corpus->rows * sizeof(int));
    if (idx == NULL) {
        fprintf(stderr, "Failed to allocate memory for idx\n");
        return -1;
    }
    //init idx values
    for (int i = 0; i < query->rows; i++) {
        for (int j = 0; j < corpus->rows; j++) {
            idx[i * corpus->rows + j] = j + 1;
        }
    }
    // print corpus for debugging
    printf("Corpus:\n");
    for (int i = 0; i < corpus->rows; i++) {
        for (int j = 0; j < corpus->cols; j++) {
            printf("%f ", corpus->data[i][j]);
        }
        printf("\n");
    }

    // print query for debugging
    printf("Query:\n");
    for (int i = 0; i < query->rows; i++) {
        for (int j = 0; j < query->cols; j++) {
            printf("%f ", query->data[i][j]);
        }
        printf("\n");
    }

    // print idx for debugging
    for (int i = 0; i < query->rows; i++) {
        for (int j = 0; j < corpus->rows; j++) {
            printf("%d ", idx[i * corpus->rows + j]);
        }
        printf("\n");
    }

    
    int corpus_n = corpus->rows;
    // Call KNN search function
    double *D = knn_search(corpus, query, k, idx);

    int *idx_new = malloc(query->rows * k * sizeof(int));
    if (idx_new == NULL) {
        fprintf(stderr, "Failed to allocate memory for idx_new\n");
        return -1;
    }
    // copy the first k elements of idx to idx_new
    for (int i = 0; i < query->rows; i++) {
        for (int j = 0; j < k; j++) {
            idx_new[i * k + j] = idx[i * corpus_n + j];
        }
    }
    free(idx);
    idx = NULL;

    double *dst = malloc(query->rows * k * sizeof(double));
    if (dst == NULL) {
        fprintf(stderr, "Failed to allocate memory for dst\n");
        return -1;
    }
    // copy the first k elements of D to dst
    for (int i = 0; i < query->rows; i++) {
        for (int j = 0; j < k; j++) {
            dst[i * k + j] = D[i * corpus_n + j];
        }
    }
    free(D);
    D = NULL;

    // print idx_new for debbuging
    for (int i = 0; i < query->rows; i++) {
        for (int j = 0; j < k; j++) {
            printf("%d ", idx_new[i * k + j]);
        }
        printf("\n");
    }

    //print dst for debugging
    for (int i = 0; i < query->rows; i++) {
        for (int j = 0; j < k; j++) {
            printf("%f ", dst[i * k + j]);
        }
        printf("\n");
    }


    // Output results to .mat file
    if (!write_mat_file(argv[4], idx_new, dst, query->rows, k)) {
        fprintf(stderr, "Failed to write results to .mat file\n");
        return -1;
    }

    // Free allocated memory (corpus and query are freed in knn_search)
    free(idx_new);
    idx_new = NULL;
    free(dst);
    dst = NULL;
    free(D);
    D = NULL;
    return 0;
}