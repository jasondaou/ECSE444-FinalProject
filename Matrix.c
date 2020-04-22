#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include <string.h>


void check_range(struct Matrix matrix, int element_row, int element_column){
	if(element_row > matrix.m || element_column > matrix.n) perror("Out of range");
}

void set_element(struct Matrix* matrix, int element_row, int element_column, int value){
	check_range(*matrix, element_row, element_column);
	int* matrix_pointer = matrix->matrix_pointer;
	int* element_pointer = matrix_pointer + element_row * matrix->n + element_column;
	*element_pointer = value;
	return;
}

int get_element(struct Matrix matrix, int element_row, int element_column){
	check_range(matrix, element_row, element_column);
	int* matrix_pointer = matrix.matrix_pointer;
	int* element_pointer = matrix_pointer + element_row * matrix.n + element_column;
	return *element_pointer;
}

int* get_row(struct Matrix matrix, size_t row_index){
	int* row_address = matrix.matrix_pointer + row_index * matrix.n;
	return row_address;
}

void set_row(struct Matrix* matrix, int row_index, int* row_values){
	for(int i = 0; i < matrix->n; i++){
		set_element(matrix, row_index, i, *(row_values+i*sizeof(int)));
	}
	return;
}

int* get_column(struct Matrix matrix, size_t column_index){
	int* column = malloc(matrix.m*sizeof(int));
	memset(column, 0, matrix.m*sizeof(int));
	for(int i = 0; i < matrix.m; i++){
		column[i] = get_element(matrix, i, column_index);
	}
	return column;
	}

void set_column(struct Matrix* matrix, int column_index, int* column_values){
	for(int i = 0; i < matrix->m; i++){
			set_element(matrix, i, column_index, column_values[i]);
		}
}

void print_array(int* array_ptr, int size){
	printf("[");
	for(int i = 0; i < size; i++){
		if(i < size - 1) printf("%d, ", array_ptr[i]);
		else printf("%d", array_ptr[i]);
	}
	printf("] \n");
}

void print_matrix(struct Matrix matrix){
	for(int i = 0; i < matrix.m; i++){
		for(int j = 0; j < matrix.n; j++){
			printf("%d\t", get_element(matrix, i, j));
		}
		printf("\n");
	}
	printf("\n");
}

struct Matrix init_empty_matrix(size_t m, size_t n){
	int* matrix_pointer = malloc(m * n * sizeof(int));
	memset(matrix_pointer, 0, m*n*sizeof(int));
	struct Matrix matrix = {.m = m, .n = n, .matrix_pointer = matrix_pointer};
	return matrix;
}

struct Matrix init_matrix(size_t m, size_t n, int* elements){
	struct Matrix matrix = {.m = m, .n = n, .matrix_pointer = malloc(m*n*sizeof(int))};
	matrix.matrix_pointer = elements;
	return matrix;
}

// int main(int argc, char *argv[]) {
// 	int double_array[9] = {1,2,3,4,5,6,7,8,9};
// 	struct Matrix test_matrix = init_matrix(3, 3, (int*)double_array);
// 	print_matrix(test_matrix);

// 	set_element(&test_matrix, 1, 1, 20);
// 	print_matrix(test_matrix);
// }