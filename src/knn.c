#include <cblas.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "knn.h"


double *knn_search(double_matrix_t* C, double_matrix_t* Q, int k, int* idx) {
    // flatten the matrices
    int corpus_n = C->rows;
    int query_n = Q->rows;
    int dim = C->cols;
    double *C_1d = convert_to_1d(C);
    double *Q_1d = convert_to_1d(Q);

    free_double_matrix(C);
    C = NULL;
    free_double_matrix(Q);
    Q = NULL;

    // allocate memory for the distance matrix
    double *D = (double *)malloc(corpus_n * query_n * sizeof(double));

    // compute 2*C*Q_T
    double* CQ_T = (double*)malloc(corpus_n * query_n * sizeof(double));
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, 
                corpus_n, query_n, dim,
                -2.0, C_1d, dim, Q_1d, dim,
                0.0, CQ_T, query_n);

    // compute C.^2
    double *C2 = (double *)malloc(corpus_n * sizeof(double));
    for (int i = 0; i < corpus_n; i++) {
        C2[i] = cblas_ddot(dim, C_1d + i*dim, 1, C_1d + i*dim, 1);
    }

    // compute Q.^2
    double *Q2 = (double *)malloc(query_n * sizeof(double));
    for (int i = 0; i < query_n; i++) {
        Q2[i] = cblas_ddot(dim, Q_1d + i*dim, 1, Q_1d + i*dim, 1);
    }

    // compute the distance matrix
    for (int i = 0; i < corpus_n; i++) {
        for (int j = 0; j < query_n; j++) {
            D[j * corpus_n + i] = sqrt(C2[i] + Q2[j] + CQ_T[i * query_n + j]);
        }
    }

    // find the k-nearest neighbors
    for (int i = 0; i < query_n; i++) {
        quickselect(D + i * corpus_n, idx + i * k, 0, corpus_n, k);
        quicksort(D + i * k, idx + i * k, k);
    }

    // free memory
    free(C_1d);
    C_1d = NULL;
    free(Q_1d);
    Q_1d = NULL;
    free(CQ_T);
    CQ_T = NULL;
    free(C2);
    C2 = NULL;
    free(Q2);
    Q2 = NULL;
    return D;
}

void quickselect(double *arr, int *idx, int start, int n, int k) { 
    int pivot = partition(arr, idx, start, n);

    if (start + pivot - 1 == k) {
        return;
    } else if (start + pivot  - 1 > k) {
        n = pivot;
        quickselect(arr, idx, start, n, k);
    } else {
        start += pivot;
        n = n - pivot;
        k = k - pivot;
        quickselect(arr + start, idx + start, start, n, k);
    }
}

int partition(double *arr, int *idx, int start, int n) {
    double pivotValue = arr[n - 1];
    int storeIndex = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < pivotValue) {
            swap_d(arr, i, storeIndex);
            swap_i(idx, i, storeIndex);
            storeIndex++;
        }
    }
    swap_d(arr, n - 1, storeIndex);
    swap_i(idx, n - 1, storeIndex);
    return storeIndex;
}