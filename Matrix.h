#include <stdio.h>

#ifndef matrix_header
#define matrix_header
/** Use single instead of double pointer to store matrix to reduce memory accesses (optimization because reduces the 
number of memory accesses).
**/

struct Matrix{
	int m, n;
	int* matrix_pointer;
};

void check_range(struct Matrix matrix, int element_row, int element_column);
void set_element(struct Matrix* matrix, int element_row, int element_column, int value);
int get_element(struct Matrix matrix, int element_row, int element_column);
int* get_row(struct Matrix matrix, size_t row_index);
void set_row(struct Matrix* matrix, int row_index, int* row_values);
int* get_column(struct Matrix matrix, size_t column_index);
void set_column(struct Matrix* matrix, int column_index, int* column_values);
void print_array(int* array_ptr, int size);
void print_matrix(struct Matrix matrix);
struct Matrix init_empty_matrix(size_t m, size_t n);
struct Matrix init_matrix(size_t m, size_t n, int* elements);

#endif