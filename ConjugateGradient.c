#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"
#include "Matrix.h"
#include "SparseMatrix.h"
#include "cholesky.h"

float dotProd(struct Matrix a, struct Matrix b) {
	if (a.n != 1 || b.n != 1)
		printf("ERROR: Dot Product could not be performed. Invalid dimensions.");	
	float sum = 0, tempA = -1, tempB = -1;
	for (int i = 0; i < a.m; i++) {
		tempA = get_element(a, i, 0);
		tempB = get_element(b, i, 0);
		sum += (tempA * tempB);
	}
	return sum;
}

struct Matrix crossProd(struct Matrix matrix, struct Matrix vector) {
	struct Matrix solution = init_empty_matrix(matrix.m, 1);
	int len = matrix.m;
	float temp;
	for (int i = 0; i < len; i++) {
		temp = 0.0;
		for (int j = 0; j < len; j++) {
			temp += get_element(matrix, i, j) * get_element(vector, j, 0);
		}
		set_element(&solution, i, 0, temp);
	}
	return solution;
}


void assignVector(struct Matrix a, struct Matrix b) {
	for (int i = 0; i < a.m; i++) {
	    set_element(&a, i, 0, get_element(b, i, 0));
	}
}





int conjugate_gradient(struct Matrix matrixA, struct Matrix matrixB, int order, float tolerance, int max_iterations) {
	double time_start, time_finish, time_elapsed;

	// Setup variables
	int count = 0;
	float alpha;
	float beta;
	struct Matrix holderVector = init_empty_matrix(order, 1);
	struct Matrix x = init_empty_matrix(order, 1);
	struct Matrix x_prev = init_empty_matrix(order, 1);
	struct Matrix s = init_empty_matrix(order, 1);
	struct Matrix p = init_empty_matrix(order, 1);
	struct Matrix p_prev = init_empty_matrix(order, 1);
	struct Matrix resVector = init_empty_matrix(order, 1);
	struct Matrix resVector_prev = init_empty_matrix(order, 1);
	struct Matrix resVector_prev_prev = init_empty_matrix(order, 1);
	
	// For each row:
	assignVector(resVector, matrixB);
	assignVector(resVector_prev, matrixB);
	assignVector(resVector_prev_prev, matrixB);

	

	// Start timer
	GET_TIME(time_start);
	while ((dotProd(resVector, resVector) > tolerance) && (count < max_iterations)) {
		count++;
		assignVector(resVector_prev_prev, resVector_prev);
		assignVector(resVector_prev, resVector);
		assignVector(p_prev, p);
		assignVector(x_prev, x);
		if (count == 1) {
			// (Direction vector) P_1 = R_0 (nResidual vector)
			assignVector(p, resVector_prev);
			assignVector(p_prev, p);

		} else {
			// b = [R_1 * R_1] / [R_0 * R_0]  
			beta = dotProd(resVector_prev, resVector_prev)/dotProd(resVector_prev_prev, resVector_prev_prev);
			// P_1 = R_1 + [beta_0 * P_0]
			deinit_matrix(holderVector);
			holderVector = scalar_product(p_prev, beta);
			deinit_matrix(p);
			p = add_matrices(resVector, holderVector);
			
		}
		// S_1 = (A * P_1) 
		deinit_matrix(s);
		s = crossProd(matrixA, p);
		
		// alpha_1 = [R_1 * R_1] / [P_1 * S_1]
		double d1 = dotProd(resVector_prev, resVector_prev);
		double d2 = dotProd(p, s);
		alpha = d1/d2;

		// X_2 = X_1 + (alpha_1 * P_1)
		deinit_matrix(holderVector);
		holderVector = scalar_product(p, alpha);
		deinit_matrix(x);
		x = add_matrices(x_prev, holderVector);
		
		// R_(k+1) = R_k - (alpha_k * S_k)
		deinit_matrix(holderVector);
		holderVector = scalar_product(s, alpha);
		deinit_matrix(resVector);
		resVector = sub_matrices(resVector_prev, holderVector);
		
	}
	
	GET_TIME(time_finish);
	time_elapsed = time_finish - time_start;
	
	printf("Time taken (seconds) CG: %lf\n", time_elapsed);
	printf("No. of iterations taken: %d \n", count);
	
	printf("Answer CG: \n");
	for (int i = 0; i < (order); i++) {
		printf("%f\n", get_element(x, i, 0));
	}	  	
	
	
	// Get residual vector
	// R_k = B - (A * X_k) 
	resVector = sub_matrices(matrixB, crossProd(matrixA, x));

    deinit_matrix(holderVector);
    deinit_matrix(x);
    deinit_matrix(x_prev);
    deinit_matrix(s);
    deinit_matrix(p);
    deinit_matrix(p_prev);
    deinit_matrix(resVector);
    deinit_matrix(resVector_prev);
    deinit_matrix(resVector_prev_prev);
		
  return 0;
}

/*
 int main(int argc, char *argv[]) {
// 	float inputA[] = {4, 1, 1, 3};
// 	float inputB[] = {1, 2};
	struct Matrix matrixA = create_spd_matrix(10, 0.3);
	struct Matrix x_actual = random_x(10);
	print_matrix(x_actual);
 	struct Matrix matrixB = multiply_matrices(matrixA, x_actual);

 	int ret = conjugate_gradient(matrixA, matrixB, 10, 0.001, 100);
}
*/