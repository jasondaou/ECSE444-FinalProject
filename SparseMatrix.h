#include <stdio.h>

#ifndef sparse_matrix_header
#define sparse_matrix_header
/** Use single instead of double pointer to store matrix to reduce memory accesses (optimization because reduces the 
number of memory accesses).
**/

struct SparseMatrix{
	int m, n;
	int size;
	int capacity;
	struct Matrix elements;
};

void check_sparse_matrix_range(struct SparseMatrix sparseMatrix, int element_row, int element_column);
void check_sparse_matrix_same_size(struct SparseMatrix sparseMatrix1, struct SparseMatrix sparseMatrix2);

struct SparseMatrix init_empty_sparse_matrix(size_t m, size_t n, int capacity);
void print_sparse_matrix(const struct SparseMatrix sparseMatrix);
void set_sparse_matrix_element(struct SparseMatrix* sparseMatrix, int element_row, int element_column, int value);
int get_sparse_matrix_element(struct SparseMatrix sparseMatrix, int element_row, int element_column);
struct SparseMatrix add_sparse_matrices(struct SparseMatrix sparseMatrix1, struct SparseMatrix sparseMatrix2);
struct SparseMatrix sub_sparse_matrices(struct SparseMatrix sparseMatrix1, struct SparseMatrix sparseMatrix2);

#endif