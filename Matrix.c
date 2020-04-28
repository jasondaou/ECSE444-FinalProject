#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"
#include <string.h>


void check_range(struct Matrix matrix, int element_row, int element_column){
	if(element_row > matrix.m || element_column > matrix.n) perror("Out of range");
}

void set_element(struct Matrix* matrix, int element_row, int element_column, float value){
	check_range(*matrix, element_row, element_column);
	float* matrix_pointer = matrix->matrix_pointer;
	float* element_pointer = matrix_pointer + element_row * matrix->n + element_column;
	*element_pointer = value;
	return;
}

float get_element(struct Matrix matrix, int element_row, int element_column){
	check_range(matrix, element_row, element_column);
	float* matrix_pointer = matrix.matrix_pointer;
	float* element_pointer = matrix_pointer + element_row * matrix.n + element_column;
	return *element_pointer;
}

float* get_row(struct Matrix matrix, size_t row_index){
	float* row_address = matrix.matrix_pointer + row_index * matrix.n;
	return row_address;
}

void set_row(struct Matrix* matrix, int row_index, float* row_values){
	for(int i = 0; i < matrix->n; i++){
		set_element(matrix, row_index, i, *(row_values+i));
	}
	return;
}

float* get_column(struct Matrix matrix, size_t column_index){
	float* column = malloc(matrix.m*sizeof(float));
	memset(column, 0, matrix.m*sizeof(float));
	for(int i = 0; i < matrix.m; i++){
		column[i] = get_element(matrix, i, column_index);
	}
	return column;
	}

void set_column(struct Matrix* matrix, int column_index, float* column_values){
	for(int i = 0; i < matrix->m; i++){
			set_element(matrix, i, column_index, column_values[i]);
		}
}

struct Matrix transpose(struct Matrix original) {
    float* values = malloc(original.m * original.n * sizeof(float));
    memset(values, 0, original.m * original.n * sizeof(float));
    struct Matrix trans = {.m = original.n, .n = original.m, .matrix_pointer = values};

    // Get row of original matrix, and set column of transpose
    for (int i = 0; i < original.m; i++) {
        float* original_row = get_row(original, i);
        set_column(&trans, i, original_row);
    }

    return trans;
}


void print_array(float* array_ptr, int size){
	printf("[");
	for(int i = 0; i < size; i++){
		if(i < size - 1) printf("%.3f, ", array_ptr[i]);
		else printf("%.3f", array_ptr[i]);
	}
	printf("] \n");
}

void print_matrix(struct Matrix matrix){
	for(int i = 0; i < matrix.m; i++){
		for(int j = 0; j < matrix.n; j++){
			printf("%.3f\t", get_element(matrix, i, j));
		}
		printf("\n");
	}
	printf("\n");
}

struct Matrix init_empty_matrix(size_t m, size_t n){
	float* matrix_pointer = malloc(m * n * sizeof(float));
	memset(matrix_pointer, 0, m*n*sizeof(float));
	struct Matrix matrix = {.m = m, .n = n, .matrix_pointer = matrix_pointer};
	return matrix;
}

struct Matrix init_matrix(size_t m, size_t n, float* elements){
	struct Matrix matrix = {.m = m, .n = n, .matrix_pointer = malloc(m*n*sizeof(float))};
	matrix.matrix_pointer = elements;
	return matrix;
}

struct Matrix clone_matrix(struct Matrix original) {
    struct Matrix clone = {.m = original.m, .n = original.n,
            .matrix_pointer = malloc(original.m*original.n*sizeof(float))};
    memcpy(clone.matrix_pointer, original.matrix_pointer, original.m * original.n * sizeof(float));
    return clone;
}

void deinit_matrix(struct Matrix matrix) {
    free(matrix.matrix_pointer);
    return;
}

void check_same_size(struct Matrix matrix1, struct Matrix matrix2){
	if(matrix1.m != matrix2.m || matrix1.n != matrix2.n) perror("Matrices should have the same size to add");
}

struct Matrix add_matrices(struct Matrix matrix1, struct Matrix matrix2){
	check_same_size(matrix1, matrix2);
	struct Matrix result_matrix = init_empty_matrix(matrix1.m, matrix1.n);
	float result = 0, element1 = 0, element2 = 0;
	for(int i = 0; i < matrix1.m; i++){
		for(int j = 0; j < matrix2.n; j++){
		    element1 = get_element(matrix1, i, j);
			element2 = get_element(matrix2, i, j);
			result = element1 + element2;
			set_element(&result_matrix, i, j, result);
		}
	}
	return result_matrix;
}

struct Matrix sub_matrices(struct Matrix matrix1, struct Matrix matrix2){
	check_same_size(matrix1, matrix2);
	struct Matrix result_matrix = init_empty_matrix(matrix1.m, matrix1.n);
	float result = 0, element1 = 0, element2 = 0;
	for(int i = 0; i < matrix1.m; i++){
		for(int j = 0; j < matrix1.n; j++){
			element1 = get_element(matrix1, i, j);
			element2 = get_element(matrix2, i, j);
			result = element1 - element2;
			set_element(&result_matrix, i, j, result);
		}
	}
	return result_matrix;
}

struct Matrix scalar_product(struct Matrix matrix, float scalar){
	struct Matrix resultMatrix = init_empty_matrix(matrix.m, matrix.n);
	float value = 0;
	for(int i = 0; i < matrix.m; i++){
		for(int j = 0; j < matrix.n; j++){
			value = get_element(matrix, i, j);
			value *= scalar;
			set_element(&resultMatrix, i, j, value);
		}
	}
	return resultMatrix;
}

struct Matrix multiply_matrices(struct Matrix matrix1, struct Matrix matrix2){
	if(matrix1.n != matrix2.m) perror("Matrix dimension don't match for multiplication");
	struct Matrix resultMatrix = init_empty_matrix(matrix1.m, matrix2.n);
	float result = 0, element1 = 0, element2 = 0;
	for(int i = 0; i < matrix1.m; i++){
		for(int j = 0; j < matrix2.n; j++){
			result = 0;
			for(int k = 0; k < matrix1.n; k++){
				element1 = get_element(matrix1, i, k);
				element2 = get_element(matrix2, k, j);
				result += element1 * element2;
			}
			set_element(&resultMatrix, i, j, result);
		}
	}
	return resultMatrix;
}

/*
int main(int argc, char *argv[]) {
 	float array[9] = {1,2,3,4,5,6,7,8,9};
 	struct Matrix matrix1 = init_matrix(3, 3, (float*)array);
 	print_matrix(matrix1);

//	int double_array_2[9] = {9,8,7,6,5,4,3,2,1};
// 	struct Matrix matrix2 = init_matrix(3, 3, (int*)double_array_2);
// 	print_matrix(matrix1);
//	print_matrix(matrix2);
//	print_matrix(multiply_matrices(matrix1, matrix2));
//

}
 */