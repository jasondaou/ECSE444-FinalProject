//
// Created by Adithya Lakshminarayanan on 27/04/2020.
//

#ifndef INC_444_CHOLESKY_H
#define INC_444_CHOLESKY_H
#include "Matrix.h"
struct Matrix cholesky_solver(struct Matrix A, struct Matrix b);
struct Matrix create_spd_matrix(int n, float sparsity);
struct Matrix random_x(int n);
#endif //INC_444_CHOLESKY_H
