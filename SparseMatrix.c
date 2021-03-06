#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "SparseMatrix.h"
#include <string.h>


void check_sparse_matrix_range(struct SparseMatrix sparseMatrix, int element_row, int element_column){
	if(element_row > sparseMatrix.m || element_column > sparseMatrix.n) perror("Out of range");
}

struct SparseMatrix init_empty_sparse_matrix(size_t m, size_t n, int capacity){
	struct Matrix sparseMatrixElements = init_empty_matrix(3, capacity);
	struct SparseMatrix sparseMatrix = {.m = m, .n = n, .size = 0,.capacity = capacity, .elements = sparseMatrixElements};
	return sparseMatrix;
}

struct SparseMatrix init_sparse_matrix(size_t m, size_t n, int capacity, int* elements){
	struct SparseMatrix sparseMatrix = init_empty_sparse_matrix(m, n, capacity);
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if(elements[i*n+j] != 0){
				set_sparse_matrix_element(&sparseMatrix, i, j, elements[i*n+j]);
			}
		}
	}
	return sparseMatrix;
}

struct Matrix sparse_to_dense_matrix(const struct SparseMatrix sparseMatrix){
	int* matrixAsArray = malloc(sparseMatrix.m * sparseMatrix.n*sizeof(int));
	memset(matrixAsArray, 0, sparseMatrix.m * sparseMatrix.n * sizeof(int));
	for(int i = 0; i < sparseMatrix.size; i++){
		int element_row = get_element(sparseMatrix.elements, 0, i);
		int element_column = get_element(sparseMatrix.elements, 1, i);
		int element_value = get_element(sparseMatrix.elements, 2, i);
		matrixAsArray[element_row * sparseMatrix.n + element_column] = element_value;
	}
	struct Matrix denseMatrix = init_matrix(sparseMatrix.m, sparseMatrix.n, matrixAsArray);
	return denseMatrix;
}

void print_sparse_matrix(const struct SparseMatrix sparseMatrix){
	struct Matrix printableMatrix = sparse_to_dense_matrix(sparseMatrix);
	print_matrix(printableMatrix);
}

void set_sparse_matrix_element(struct SparseMatrix* sparseMatrix, int element_row, int element_column, int value){
	check_sparse_matrix_range(*sparseMatrix, element_row, element_column);
	// If the element is non-zero, modify it
	for(int i = 0; i < sparseMatrix->size; i++){
		if (get_element(sparseMatrix->elements, 0, i) == element_row){
			if (get_element(sparseMatrix->elements, 1, i) == element_column){
				//Modify an existing elements
				set_element(&sparseMatrix->elements, 2, i, value);
				return;
			}
		}
	}
	//Add an element
	if(sparseMatrix->size < sparseMatrix->capacity){
		set_element(&(sparseMatrix->elements), 0, sparseMatrix->size, element_row);
		set_element(&(sparseMatrix->elements), 1, sparseMatrix->size, element_column);
		set_element(&(sparseMatrix->elements), 2, sparseMatrix->size, value);
		sparseMatrix->size += 1;
	}
	else{
		//Create a matrix with double the capcity
		struct SparseMatrix biggerSparseMatrix = init_empty_sparse_matrix(sparseMatrix->m, sparseMatrix->n, sparseMatrix->capacity * 2);
		// Copy all the existing elements
		for(int i = 0; i < sparseMatrix->capacity; i++){
			set_element(&(biggerSparseMatrix.elements), 0, i, get_element(sparseMatrix->elements, 0, i));
			set_element(&(biggerSparseMatrix.elements), 1, i, get_element(sparseMatrix->elements, 1, i));
			set_element(&(biggerSparseMatrix.elements), 2, i, get_element(sparseMatrix->elements, 2, i));
			biggerSparseMatrix.size += 1;

		}
		//Add the new element
		set_element(&(biggerSparseMatrix.elements), 0, biggerSparseMatrix.size, element_row);
		set_element(&(biggerSparseMatrix.elements), 1, biggerSparseMatrix.size, element_column);
		set_element(&(biggerSparseMatrix.elements), 2, biggerSparseMatrix.size, value);
		biggerSparseMatrix.size += 1;
		free(sparseMatrix->elements.matrix_pointer);
		

		sparseMatrix->elements = biggerSparseMatrix.elements;
		sparseMatrix->size += 1;
		sparseMatrix->capacity *= 2;
		
	}
	return;
}

int get_sparse_matrix_element(struct SparseMatrix sparseMatrix, int element_row, int element_column){
	check_sparse_matrix_range(sparseMatrix, element_row, element_column);
	for(int i = 0; i < sparseMatrix.size; i++){
		if(get_element(sparseMatrix.elements, 0, i) == element_row){
			if(get_element(sparseMatrix.elements, 1, i) == element_column){
				return get_element(sparseMatrix.elements, 2, i);
			}
		}
	}
	return 0;
}

void check_sparse_matrix_same_size(struct SparseMatrix sparseMatrix1, struct SparseMatrix sparseMatrix2){
		if(sparseMatrix1.m != sparseMatrix2.m || sparseMatrix1.n != sparseMatrix2.n) perror("Matrices should have the same size to add");
}

struct SparseMatrix add_sparse_matrices(struct SparseMatrix sparseMatrix1, struct SparseMatrix sparseMatrix2){
	check_sparse_matrix_same_size(sparseMatrix1, sparseMatrix2);
	int biggest_capacity = sparseMatrix1.capacity > sparseMatrix2.capacity ? sparseMatrix1.capacity : sparseMatrix2.capacity;
	struct SparseMatrix resultMatrix = init_empty_sparse_matrix(sparseMatrix1.m, sparseMatrix1.n, biggest_capacity);
	int result = 0, element1 = 0, element2 = 0;
	for(int i = 0; i < sparseMatrix1.m; i++){
		for(int j = 0; j < sparseMatrix1.n; j++){
			int element1 = get_sparse_matrix_element(sparseMatrix1, i, j);
			int element2 = get_sparse_matrix_element(sparseMatrix2, i, j);
			result = element1 + element2;
			set_sparse_matrix_element(&resultMatrix, i, j, result);
		}
	}
	return resultMatrix;
}

struct SparseMatrix sub_sparse_matrices(struct SparseMatrix sparseMatrix1, struct SparseMatrix sparseMatrix2){
	check_sparse_matrix_same_size(sparseMatrix1, sparseMatrix2);
	int biggest_capacity = sparseMatrix1.capacity > sparseMatrix2.capacity ? sparseMatrix1.capacity : sparseMatrix2.capacity;
	struct SparseMatrix resultMatrix = init_empty_sparse_matrix(sparseMatrix1.m, sparseMatrix1.n, biggest_capacity);
	int result = 0, element1 = 0, element2 = 0;
	for(int i = 0; i < sparseMatrix1.m; i++){
		for(int j = 0; j < sparseMatrix1.n; j++){
			int element1 = get_sparse_matrix_element(sparseMatrix1, i, j);
			int element2 = get_sparse_matrix_element(sparseMatrix2, i, j);
			result = element1 - element2;
			set_sparse_matrix_element(&resultMatrix, i, j, result);
		}
	}
	return resultMatrix;
}

struct SparseMatrix scalar_product_sparse_matrix(struct SparseMatrix sparseMatrix, int scalar){
	struct SparseMatrix resultMatrix = init_empty_sparse_matrix(sparseMatrix.m, sparseMatrix.n, sparseMatrix.capacity);
	int value = 0;
	for(int i = 0; i < sparseMatrix.m; i++){
		for(int j = 0; j < sparseMatrix.n; j++){
			value = get_sparse_matrix_element(sparseMatrix, i, j);
			value *= scalar;
			set_sparse_matrix_element(&resultMatrix, i, j, value);
		}
	}
	return resultMatrix;
}

struct SparseMatrix multiply_sparse_matrices(struct SparseMatrix sparseMatrix1, struct SparseMatrix sparseMatrix2){
	int biggest_capacity = sparseMatrix1.capacity > sparseMatrix2.capacity ? sparseMatrix1.capacity : sparseMatrix2.capacity;
	if(sparseMatrix1.n != sparseMatrix2.m) perror("Matrix dimension don't match for multiplication");
	struct SparseMatrix resultMatrix = init_empty_sparse_matrix(sparseMatrix1.m, sparseMatrix2.n, biggest_capacity);
	int result = 0, element1 = 0, element2 = 0;
	for(int i = 0; i < sparseMatrix1.m; i++){
		for(int j = 0; j < sparseMatrix2.n; j++){
			result = 0;
			for(int k = 0; k < sparseMatrix1.n; k++){
				element1 = get_sparse_matrix_element(sparseMatrix1, i, k);
				element2 = get_sparse_matrix_element(sparseMatrix2, k, j);
				result += element1 * element2;
			}
			set_sparse_matrix_element(&resultMatrix, i, j, result);
		}
	}
	return resultMatrix;
}


// int main(int argc, char *argv[]) {
// 	struct SparseMatrix test = init_empty_sparse_matrix(3, 3, 1);
	
// 	set_sparse_matrix_element(&test, 0, 0, -1);
// 	set_sparse_matrix_element(&test, 1, 1, 2);
// 	set_sparse_matrix_element(&test, 1, 1, 3);
// 	set_sparse_matrix_element(&test, 1, 2, 3);
// 	set_sparse_matrix_element(&test, 2, 1, 3);
// 	set_sparse_matrix_element(&test, 2, 2, 5);
// 	print_sparse_matrix(test);
	
// 	struct SparseMatrix test2 = init_empty_sparse_matrix(3, 3, 1);
		
// 	set_sparse_matrix_element(&test2, 0, 0, 1);
// 	set_sparse_matrix_element(&test2, 1, 1, 2);
// 	set_sparse_matrix_element(&test2, 1, 1, 3);
// 	set_sparse_matrix_element(&test2, 1, 2, 3);
// 	set_sparse_matrix_element(&test2, 2, 1, 3);
// 	set_sparse_matrix_element(&test2, 2, 2, 5);
// 	print_sparse_matrix(test2);

// 	print_sparse_matrix(multiply_sparse_matrices(test, test2));
// 	int elements[9] = {1,2,3,0,0,0,0,0,0};
// 	print_sparse_matrix(init_sparse_matrix(3,3,3,(int*)elements));


// 	return 0;
	
// }