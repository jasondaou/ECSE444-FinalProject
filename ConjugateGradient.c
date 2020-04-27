#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "timer.h"


double* vectorAdd(double* destination, double* a, double* b, int len) {
	for (int i = 0; i < len; i++) {
		destination[i] = a[i] + b[i];
	}
	return destination;
}

double* vectorSub(double* destination, double* a, double* b, int len) {
	for (int i = 0; i < len; i++) {
		destination[i] = a[i] - b[i];
	}
	return destination;
}

double dotProd(double* a, double* b, int len) {
	double sum = 0.0;
	for (int i = 0; i < len; i++) {
		sum += (a[i] * b[i]);
	}
	return sum;
}

double* crossProd(double* destination, double* matrix, double* vector, int len) {
	for (int i = 0; i < len; i++) {
		destination[i] = 0.0;
		for (int j = 0; j < len; j++) {
			destination[i] += matrix[i*len+j] * vector[j];
		}
	}
	return destination;
}

double* scalarProd(double* destination, double* vector, double scalar, int len) {
	for (int i = 0; i < len; i++) {
		destination[i] = scalar * vector[i];
	}
	return destination;
}

void assignVector(double* a, double* b, int len) {
	for (int i = 0; i < len; i++) {
		a[i] = b[i];
	}
}





int main(int argc, char **argv) {
	double time_start, time_finish, time_elapsed;


	if (argc == 4) {
		// Parsing arguments
		// Matrix A dimensions
		int order = atoi(argv[1]); 
		// Tolderance of solution
		double tolerance = atof(argv[2]);
		// Max iterations taken for solution
		int max_iterations = atoi(argv[3]); 
		

		// Setup matrix A
		double* matrix = malloc(order * order * sizeof(double)); 
		// Setup matrix B (Right hand side)
		double* rhs = malloc(order * sizeof(double));
		
		
		// Input Matrix A
		printf("Input Matrix A: \n");
		for (int i = 0; i < order; i++) { /* number of rows */
			for (int j = 0; j < order; j++) { /* number of cols */
				if (!scanf("%lf", &matrix[(i * order) + j])) {
					break;
				}
			}
		}
		
		// Input Matrix B
		printf("Input Matrix B: \n");
		for (int i = 0; i < order; i++) {
			if (!scanf("%lf", &rhs[i])) {
				break;
			}
		}
		
		
		// Setup variables
		double* holderVector = malloc(order * sizeof(double));
		int count = 0;
		double alpha;
		double beta;
		double* x = malloc(order * sizeof(double));
		double* s = malloc(order * sizeof(double));
		double* x_prev = malloc(order * sizeof(double));
		double* p = malloc(order * sizeof(double));
		double* p_prev = malloc(order * sizeof(double));
		double* resVector = malloc(order * sizeof(double));
		double* resVector_prev = malloc(order * sizeof(double));
		double* resVector_prev_prev = malloc(order * sizeof(double));
		
		// For each row:
		for (int i = 0; i < order; i++) {
			resVector[i] = rhs[i];
			resVector_prev[i] = rhs[i];
			resVector_prev_prev[i] = rhs[i];
			x[i] = 0;
		}
		
		// Start timer
		GET_TIME(time_start);
		

		while ((dotProd(resVector, resVector, order) > tolerance) && (count < max_iterations)) {
			count++;
			assignVector(resVector_prev_prev, resVector_prev, order);
			assignVector(resVector_prev, resVector, order);
			assignVector(p_prev, p, order);
			assignVector(x_prev, x, order);
			if (count == 1) {
				// (Direction vector) P_1 = R_0 (Residual vector)
				memcpy(p, resVector_prev, (order * sizeof(double)));
				memcpy(p_prev, p, (order * sizeof(double)));

			} else {
				// b = [R_1 * R_1] / [R_0 * R_0]  
				beta = dotProd(resVector_prev, resVector_prev, order)/dotProd(resVector_prev_prev, resVector_prev_prev, order);
				// P_1 = R_1 + [beta_0 * P_0] */
				holderVector = scalarProd(holderVector, p_prev, beta, order);
				p = vectorAdd(p, resVector, holderVector, order);
				
			}
			// S_1 = (A * P_1) 
			s = crossProd(s, matrix, p, order);
		
			// alpha_1 = [R_1 * R_1] / [P_1 * S_1]
			double d1 = dotProd(resVector_prev, resVector_prev, order);
			double d2 = dotProd(p, s, order);
			alpha = d1/d2;
			
			// X_2 = X_1 + (alpha_1 * P_1)
			holderVector = scalarProd(holderVector, p, alpha, order);
			x = vectorAdd(x, x_prev, holderVector, order);
			
			// R_(k+1) = R_k - (alpha_k * S_k)
			holderVector = scalarProd(holderVector, s, alpha, order);
			resVector = vectorSub(resVector, resVector_prev, holderVector, order);
			
		}
		
		GET_TIME(time_finish);
		time_elapsed = time_finish - time_start;
		
		printf("Time taken (seconds): %lf\n", time_elapsed);
		printf("No. of iterations taken: %d \n", count);
		
		printf("Answer: \n");
		for (int i = 0; i < (order); i++) {
			printf("%f\n", x[i]);
		}	  	
		
		printf("The norm of the residual calculated by the conjugate gradient method: \n");
		double norm = 9999.9999;
		for (int i = 0; i < (order); i++) {
			norm += resVector[i]*resVector[i];
		}
		printf("%lf\n", sqrt(norm));
		
		
		/* Calculate the residual with the algorithm
			R_k = B - (A * X_k) */
		resVector = vectorSub(resVector, rhs, crossProd(holderVector, matrix, x, order), order);
		
		
		printf("The norm of the residual calculated directly from the definition of residual: \n");
		for (int i = 0; i < (order * order); i++) {
			norm += resVector[i]*resVector[i];
		}
		printf("%lf\n", sqrt(norm));
		


		// Free memory
		free(matrix);
		free(rhs);
		free(x);
		free(s);
		free(p);
		free(resVector);
		free(x_prev);
		free(p_prev);
		free(resVector_prev);
		free(resVector_prev_prev);
		free(holderVector);

		
	} else {
	  printf("ERROR: 3 Arguments needed = [order] [tolerance] [iterations] \n");
  }
  
  return 0;
}