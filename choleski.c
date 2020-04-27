#include "Matrix.h"
#include "SparseMatrix.h"
#include <math.h>
#include <stdlib.h>

int RAND_RANGE = 50;

struct Matrix choleski_solver(struct Matrix A, struct Matrix b) {

    // Clone matrices in order to perform in place computation
    struct Matrix A_clone = clone_matrix(A);
    struct Matrix b_clone = clone_matrix(b);

    // Dimension along one side of matrix (should be square)
    int n = A_clone.m;

    // Traverse columns, and perform in place computation for L instead of A, and y in place of b
    float temp_value;
    float A_ij;
    for(int j = 0; j < n; j++) {
        // L[j, j] = sqrt(A[j, j])
        temp_value = sqrt(get_element(A_clone, j, j));
        set_element(&A_clone, j, j, temp_value);

        // y[j, 0] = b[j, 0] / A[j, j]
        temp_value = get_element(b_clone, j, 0) / get_element(A_clone, j, j);
        set_element(&b_clone, j, 0, temp_value);

        for(int i = j + 1; i < n; i++) {
            // L[i, j] = L[i, j] / L[j, j]
            temp_value = get_element(A_clone, i, j) / get_element(A_clone, j, j);
            set_element(&A_clone, i, j, temp_value);
            // Look ahead update:  b[i, 0] = b[i, 0] - L[i, j] * b[j, 0]
            temp_value = get_element(b_clone, i, 0) - get_element(A_clone, i, j) * get_element(b_clone, j, 0);
            set_element(&b_clone, i, 0, temp_value);

            // Look ahead modification on L
            A_ij = get_element(A_clone, i, j);
            for(int k = j + 1; k < (i + 1); k++) {
                temp_value = -1 * A_ij * get_element(A_clone, k, j);
                temp_value += get_element(A_clone, i, k);
                set_element(&A_clone, i, k, temp_value);
            }
        }
    }

    print_matrix(A_clone);
    print_matrix(b_clone);

    // By here, L has been computed in place of A, and y in place of b
    // Initialize solution matrix, x
    struct Matrix x = init_empty_matrix(n, 1);
    float partial_product = 0;
    // Compute starting from x[n -1, 0] backwards
    for (int i = n - 1; i >= 0; i--) {

        partial_product = 0;

        for(int j = i + 1; j < n; j++) {
            partial_product += get_element(A_clone, j, i) * get_element(x, j, 0);
        }

        temp_value = get_element(b_clone, i, 0) - partial_product;
        temp_value /= get_element(A_clone, i, i);
        set_element(&x, i, 0, temp_value);
    }

    // De-initialize cloned matrices to free memory
    deinit_matrix(A_clone);
    deinit_matrix(b_clone);

    // return solution to Ax = b
    return x;
}

struct Matrix sparse_choleski_solver(struct SparseMatrix A, struct Matrix b) {

    // Clone matrices in order to perform in place computation
    struct Matrix A_clone = clone_matrix(A);
    struct Matrix b_clone = clone_matrix(b);

    // Dimension along one side of matrix (should be square)
    int n = A_clone.m;

    // Traverse columns, and perform in place computation for L instead of A, and y in place of b
    float temp_value;
    float A_ij;
    for(int j = 0; j < n; j++) {
        // L[j, j] = sqrt(A[j, j])
        temp_value = sqrt(get_element(A_clone, j, j));
        set_element(&A_clone, j, j, temp_value);

        // y[j, 0] = b[j, 0] / A[j, j]
        temp_value = get_element(b_clone, j, 0) / get_element(A_clone, j, j);
        set_element(&b_clone, j, 0, temp_value);

        for(int i = j + 1; i < n; i++) {
            // L[i, j] = L[i, j] / L[j, j]
            temp_value = get_element(A_clone, i, j) / get_element(A_clone, j, j);
            set_element(&A_clone, i, j, temp_value);
            // Look ahead update:  b[i, 0] = b[i, 0] - L[i, j] * b[j, 0]
            temp_value = get_element(b_clone, i, 0) - get_element(A_clone, i, j) * get_element(b_clone, j, 0);
            set_element(&b_clone, i, 0, temp_value);

            // Look ahead modification on L
            A_ij = get_element(A_clone, i, j);
            for(int k = j + 1; k < (i + 1); k++) {
                temp_value = -1 * A_ij * get_element(A_clone, k, j);
                temp_value += get_element(A_clone, i, k);
                set_element(&A_clone, i, k, temp_value);
            }
        }
    }

    print_matrix(A_clone);
    print_matrix(b_clone);

    // By here, L has been computed in place of A, and y in place of b
    // Initialize solution matrix, x
    struct Matrix x = init_empty_matrix(n, 1);
    float partial_product = 0;
    // Compute starting from x[n -1, 0] backwards
    for (int i = n - 1; i >= 0; i--) {

        partial_product = 0;

        for(int j = i + 1; j < n; j++) {
            partial_product += get_element(A_clone, j, i) * get_element(x, j, 0);
        }

        temp_value = get_element(b_clone, i, 0) - partial_product;
        temp_value /= get_element(A_clone, i, i);
        set_element(&x, i, 0, temp_value);
    }

    // De-initialize cloned matrices to free memory
    deinit_matrix(A_clone);
    deinit_matrix(b_clone);

    // return solution to Ax = b
    return x;
}

/*
 * Generate an SPD matrix by generating a random lower-triangular matrix, L.
 * SPD matrix can then be generated by multiplying L by its transpose
 */
struct Matrix create_spd_matrix(int n) {
    struct Matrix l = init_empty_matrix(n, n);

    // random lower-triangular matrix
    for(int j = 0; j < l.m; j++) {
        for (int i = 0; i <= j; i ++) {
            set_element(&l, i, j, rand() % RAND_RANGE);
        }
    }

    struct Matrix l_t = transpose(l);

    struct Matrix spd = multiply_matrices(l, l_t);

    // free unecessary space
    deinit_matrix(l);
    deinit_matrix(l_t);

    return spd;
}


/*
 * Create random x matrix in order to test solvers
 */
struct Matrix random_x(int n) {
    struct Matrix x = init_empty_matrix(n, 1);

    for (int i = 0; i < x.m; i++) {
        set_element(&x, i, 0, rand() % RAND_RANGE);
    }

    return x;
}

int main() {


    struct Matrix spd = create_spd_matrix(2);
    printf("spd \n");
    print_matrix(spd);
    struct Matrix x = random_x(2);
    printf("Actual x \n");
    print_matrix(x);
    struct Matrix b = multiply_matrices(spd, x);
    printf("b \n");
    print_matrix(b);
    struct Matrix choleski_x = choleski_solver(spd, b);
    printf("choleski x \n");
    print_matrix(choleski_x);
}