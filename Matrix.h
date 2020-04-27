#include <stdio.h>

#ifndef matrix_header
#define matrix_header
/** Use single instead of double pointer to store matrix to reduce memory accesses (optimization because reduces the 
number of memory accesses).
**/

struct Matrix{
	int m, n;
	float* matrix_pointer;
};

void check_range(struct Matrix matrix, int element_row, int element_column);
void check_same_size(struct Matrix matrix1, struct Matrix matrix2);
void set_element(struct Matrix* matrix, int element_row, int element_column, float value);
float get_element(struct Matrix matrix, int element_row, int element_column);
float* get_row(struct Matrix matrix, size_t row_index);
void set_row(struct Matrix* matrix, int row_index, float* row_values);
float* get_column(struct Matrix matrix, size_t column_index);
void set_column(struct Matrix* matrix, int column_index, float* column_values);
void print_array(float* array_ptr, int size);
void print_matrix(struct Matrix matrix);
struct Matrix init_empty_matrix(size_t m, size_t n);
struct Matrix init_matrix(size_t m, size_t n, float* elements);
struct Matrix clone_matrix(struct Matrix);
void deinit_matrix(struct Matrix matrix);
struct Matrix transpose(struct Matrix original);
struct Matrix add_matrices(struct Matrix matrix1, struct Matrix matrix2);
struct Matrix sub_matrices(struct Matrix matrix1, struct Matrix matrix2);
struct Matrix scalar_product(struct Matrix matrix, float scalar);
struct Matrix multiply_matrices(struct Matrix matrix1, struct Matrix matrix2);
#endif