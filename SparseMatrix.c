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




int main(int argc, char *argv[]) {
	struct SparseMatrix test = init_empty_sparse_matrix(3, 3, 1);
	print_sparse_matrix(test);
	
	set_sparse_matrix_element(&test, 0, 0, 1);
	print_sparse_matrix(test);
	
	set_sparse_matrix_element(&test, 1, 1, 2);
	print_sparse_matrix(test);
	
	set_sparse_matrix_element(&test, 1, 1, 3);
	print_sparse_matrix(test);
	
	set_sparse_matrix_element(&test, 1, 2, 3);
	print_sparse_matrix(test);
	
	set_sparse_matrix_element(&test, 2, 1, 3);
	print_sparse_matrix(test);
	
	set_sparse_matrix_element(&test, 2, 2, 5);
	print_sparse_matrix(test);
	
	printf("%d", get_sparse_matrix_element(test, 2, 1));

	return 0;
	
}