#ifndef KNN_H
#define KNN_H

#include "utils.h"


/**
 * @brief Perform k-nearest neighbors search.
 *
 * This function searches for the k-nearest neighbors of each point in the query matrix Q
 * within the reference matrix C. The indices of the nearest neighbors and their distances
 * are stored in the provided idx and dst arrays, respectively.
 *
 * @param C Pointer to the reference matrix of size (n x d), where n is the number of points and d is the dimensionality.
 * @param Q Pointer to the query matrix of size (m x d), where m is the number of query points and d is the dimensionality.
 * @param k The number of nearest neighbors to search for each query point.
 * @param idx Pointer to an array of size (m x k) where the indices of the nearest neighbors will be stored.
 */
double *knn_search(double_matrix_t* C, double_matrix_t* Q, int k, int* idx);


/**
 * @brief Finds the k-nearest neighbors for a set of query points.
 *
 * This function computes the k-nearest neighbors for each query point in a dataset.
 *
 * @param D A pointer to the distance matrix. The matrix should be of size (query__n * corpus_n).
 * @param corpus_n The number of points in the corpus dataset.
 * @param query_n The number of query points.
 * @param k The number of nearest neighbors to find.
 * @param idx A pointer to an array where the indices of the nearest neighbors will be stored.
 */
void find_knn(double *D,int corpus_n, int query_n, int k, int *idx);


/**
 * @brief Performs the quickselect algorithm to find the k-th smallest element in an array.
 *
 * This function rearranges the elements in the array such that the k-th smallest element
 * is in its correct position, and all elements smaller than it are before it, and all
 * elements greater than it are after it.
 *
 * @param arr Pointer to the flattened 2D->1D array of doubles to be partitioned.
 * @param idx Pointer to the array of indices corresponding to the elements in arr.
 * @param dst Pointer to the array where the distances of the k smallest elements from the query points will be stored.
 * @param start The starting index of the portion of the array to be partitioned (0-based).
 * @param n The number of elements in each row (segment) of the array.
 * @param k The index (1-based) of the k-th smallest element to find.
 */
void quickselect(double *arr, int *idx, int start, int n, int k); 


/**
 * @brief Partitions the array for the k-nearest neighbors algorithm.
 *
 * This function rearranges the elements in arr, such that the elements before the pivot
 * are less than or equal to the pivot, and the elements after the pivot are greater than  
 * the pivot. The pivot is chosen as the last element in the array.
 *
 * @param arr Pointer to the array of elements to be partitioned.
 * @param idx Pointer to the array of indices corresponding to the elements in `arr`.
 * @param start The starting index of the partitioning range.
 * @param n The total number of elements in the array.
 * @param k The number of smallest elements to partition.
 * @return The index of the partition point.
 */
int partition(double *arr, int *idx, int start, int n);

void swap_d(double *arr, int i, int j);
void swap_i(int *arr, int i, int j);

#endif  // KNN_H
