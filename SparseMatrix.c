#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"


struct SparseMatrix{
	int m, n;
	int size;
	int capacity;
	struct Matrix elements;
};

struct SparseMatrix init_empty_sparse_matrix(size_t m, size_t n, int capacity){
	struct Matrix sparseMatrixElements = init_empty_matrix(3, capacity);
	struct SparseMatrix sparseMatrix = {.m = m, .n = n, .size = 0,.capacity = capacity, .elements = sparseMatrixElements};
	return sparseMatrix;
}

void set_sparse_matrix_element(struct SparseMatrix sparseMatrix, int element_row, int element_column, int value){
	check_range(sparseMatrix.elements, element_row, element_column);
	for(int i = 0; i < sparseMatrix.size; i++){
		if (get_element(sparseMatrix.elements, 0, i) == element_row){
			if (get_element(sparseMatrix.elements, 1, i) == element_column){
				//Modify an existing elements
				set_element(sparseMatrix.elements, 2, i, value);
				return;
			}
		}
	}
	//Add an element
	sparseMatrix.size += 1;
	if(sparseMatrix.size < sparseMatrix.capacity){
		set_element(sparseMatrix.elements, 0, sparseMatrix.size, element_row);
		set_element(sparseMatrix.elements, 1, sparseMatrix.size, element_column);
		set_element(sparseMatrix.elements, 2, sparseMatrix.size, value);
	}
	else{
		struct SparseMatrix biggerSparseMatrix = init_empty_sparse_matrix(sparseMatrix.m, sparseMatrix.n, sparseMatrix.capacity*2);
		for(int i = 0; i < sparseMatrix.capacity; i++){
			set_element(biggerSparseMatrix.elements, 0, i, get_element(sparseMatrix.elements, 0, i));
			set_element(biggerSparseMatrix.elements, 1, i, get_element(sparseMatrix.elements, 1, i));
			set_element(biggerSparseMatrix.elements, 2, i, get_element(sparseMatrix.elements, 2, i));

		}
//		free(sparseMatrix.elements.matrix_pointer);
		sparseMatrix = biggerSparseMatrix;
	}
	return;
}
//
//int get_element(struct SparseMatrix matrix, int element_row, int element_column){
//	check_range(sparseMatrix, element_row, element_column);
//	int* matrix_pointer = matrix.matrix_pointer;
//	int* element_pointer = matrix_pointer + element_row * matrix.n + element_column;
//	return *element_pointer;
//}

//void print_sparse_matrix(struct SparseMatrix sparseMatrix){
//	for(int i = 0; i < sparseMatrix.m; i++){
//		for(int j = 0; j < sparseMatrix.n; j++){
//			printf("%d\t", get_element(matrix, i, j));
//		}
//		printf("\n");
//	}
//	printf("\n");
//}


int main(int argc, char *argv[]) {
	struct SparseMatrix test = init_empty_sparse_matrix(3, 3, 1);
	print_matrix(test.elements);
	set_sparse_matrix_element(test, 0, 0, 1);
	print_matrix(test.elements);
	set_sparse_matrix_element(test, 1, 1, 2);
	print_matrix(test.elements);

	
}