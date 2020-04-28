#include "Matrix.h"
#include "timer.h"
#include "cholesky.h"
#include "ConjugateGradient.h"

int main() {
	int i = 2;
	double time_start, time_finish, time_elapsed;
	// Size of matrix
	printf("MATRIX SIZE \n");
	for(i = 2; i < 100; i+= 10){
		printf("Matrix size: %d\n", i);
		struct Matrix spd = create_spd_matrix(i, 0.5);
		struct Matrix x = random_x(i);
		//printf("Actual x \n");
		//print_matrix(x);
		struct Matrix b = multiply_matrices(spd, x);

    	GET_TIME(time_start);
    	struct Matrix choleski_x = cholesky_solver(spd, b);
    	GET_TIME(time_finish);
    	time_elapsed = time_finish - time_start;
    	printf("Time taken (seconds) Cholesky: %.10lf\n", time_elapsed);
    	//printf("Cholesky x \n");
    	//print_matrix(choleski_x);

	    int res = conjugate_gradient(spd, b, i, 0.0000001, 1000);

	    deinit_matrix(spd);
	    deinit_matrix(x);
	    deinit_matrix(b);
	    deinit_matrix(choleski_x);
	    printf("\n");
	}

	printf("\n ******************* \n");
//	Sparsity of matrix
	double j = 0.0;
	printf("MATRIX SPARSITY\n");
	for(j = 0.0; j < 1; j += 0.1){
		printf("Sparsity ratio: %lf\n", j);
		struct Matrix spd = create_spd_matrix(5, j);
		struct Matrix x = random_x(5);
		//printf("Actual x \n");
		//print_matrix(x);
		struct Matrix b = multiply_matrices(spd, x);

    	GET_TIME(time_start);
    	struct Matrix choleski_x = cholesky_solver(spd, b);
    	GET_TIME(time_finish);
    	time_elapsed = time_finish - time_start;
    	printf("Time taken (seconds) Cholesky: %.10lf\n", time_elapsed);
    	//printf("Cholesky x \n");
    	//print_matrix(choleski_x);

	    int res = conjugate_gradient(spd, b, 5, 0.0000001, 1000);

	    deinit_matrix(spd);
	    deinit_matrix(x);
	    deinit_matrix(b);
	    deinit_matrix(choleski_x);
	    printf("\n");
	}

	printf("\n ******************* \n");
	// CG tolerance
	printf("CG TOLERANCE\n");
	for(j = 0.0000001; j < 0.000001; j += 0.0000001){
		printf("CG tolerance: %.10lf\n", j);
		struct Matrix spd = create_spd_matrix(5, 0.5);
		struct Matrix x = random_x(5);
		//printf("Actual x \n");
		//print_matrix(x);
		struct Matrix b = multiply_matrices(spd, x);

	    int res = conjugate_gradient(spd, b, 5, j, 1000);

	    deinit_matrix(spd);
	    deinit_matrix(x);
	    deinit_matrix(b);
	    printf("\n");
	}		

}