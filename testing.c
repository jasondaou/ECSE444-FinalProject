#include "Matrix.h"
#include "timer.h"
#include "cholesky.h"
#include "ConjugateGradient.h"

int main() {
	int i = 2;
	double time_start, time_finish, time_elapsed;
	// Size of matrix
	// printf("MATRIX SIZE \n")
	// for(i = 2; i < 20; i++){
	// 	printf("Matrix size: %d\n", i);
	// 	struct Matrix spd = create_spd_matrix(i, 0.5);
	// 	struct Matrix x = random_x(i);
	// 	printf("Actual x \n");
	//	print_matrix(x);
	// 	struct Matrix b = multiply_matrices(spd, x);
 //    	printf("CHOLESKY: \n");

 //    	GET_TIME(time_start);
 //    	struct Matrix choleski_x = cholesky_solver(spd, b);
 //    	GET_TIME(time_finish);
 //    	printf("Cholesky x \n");
 //    	print_matrix(choleski_x);
 //    	time_elapsed = time_finish - time_start;
 //    	printf("Time taken (seconds) Cholesky: %lf\n", time_elapsed);

	//     int res = conjugate_gradient(spd, b, i, 0.001, 1000);

	//     deinit_matrix(spd);
	//     deinit_matrix(x);
	//     deinit_matrix(b);
	//     deinit_matrix(choleski_x);
	// }

		printf("Matrix size: %d\n", 3);
		struct Matrix spd = create_spd_matrix(3, 0.5);
		struct Matrix x = random_x(3);
		struct Matrix b = multiply_matrices(spd, x);
    	printf("CHOLESKY: \n");

    	GET_TIME(time_start);
    	struct Matrix choleski_x = cholesky_solver(spd, b);
    	GET_TIME(time_finish);
    	printf("Cholesky x \n");
    	print_matrix(choleski_x);
    	time_elapsed = time_finish - time_start;
    	printf("Time taken (seconds) Cholesky: %lf\n", time_elapsed);
    	printf("Actual x \n");
	    int res = conjugate_gradient(spd, b, 3, 0.001, 1000);
	    print_matrix(x);

	    deinit_matrix(spd);
	    deinit_matrix(x);
	    deinit_matrix(b);
	    deinit_matrix(choleski_x);

	// Sparsity of matrix
	double j = 0.0;
	printf("MATRIX SPARSITY\n");
	for(j = 0.0; j < 1; j += 0.1){
		printf("Sparsity ratio: %lf\n", j);
		struct Matrix spd = create_spd_matrix(5, j);
		struct Matrix x = random_x(5);
		printf("Actual x \n");
		struct Matrix b = multiply_matrices(spd, x);
    	printf("CHOLESKY: \n");

    	GET_TIME(time_start);
    	struct Matrix choleski_x = cholesky_solver(spd, b);
    	GET_TIME(time_finish);
    	printf("Cholesky x \n");
    	print_matrix(choleski_x);
    	time_elapsed = time_finish - time_start;
    	printf("Time taken (seconds) Cholesky: %lf\n", time_elapsed);

	    int res = conjugate_gradient(spd, b, 5, 0.001, 1000);

	    deinit_matrix(spd);
	    deinit_matrix(x);
	    deinit_matrix(b);
	    deinit_matrix(choleski_x);
	}

	// CG tolerance
	printf("CG TOLERANCE\n")
	for(j = 0.001; j < 0.01; j += 0.001){
		printf("CG tolerance: %lf\n", j);
		struct Matrix spd = create_spd_matrix(5, 0.5);
		struct Matrix x = random_x(5);
		printf("Actual x \n");
		struct Matrix b = multiply_matrices(spd, x);

	    int res = conjugate_gradient(spd, b, 5, j, 1000);

	    deinit_matrix(spd);
	    deinit_matrix(x);
	    deinit_matrix(b);
	}

	// CG iterations number
	printf("CG NB OF ITERATIONS\n")
	for(i = 100; i < 1000; i += 100){
		printf("CG tolerance: %d\n", i);
		struct Matrix spd = create_spd_matrix(5, 0.5);
		struct Matrix x = random_x(5);
		printf("Actual x \n");
		struct Matrix b = multiply_matrices(spd, x);

	    int res = conjugate_gradient(spd, b, 5, 0.001, i);

	    deinit_matrix(spd);
	    deinit_matrix(x);
	    deinit_matrix(b);
	}		

}