#include <stdio.h>

#ifndef conjugate_gradient_header
#define conjugate_gradient_header

float dotProd(struct Matrix a, struct Matrix b);
struct Matrix crossProd(struct Matrix matrix, struct Matrix vector);
void assignVector(struct Matrix a, struct Matrix b);
int conjugate_gradient(int order, float tolerance, int max_iterations);


#endif