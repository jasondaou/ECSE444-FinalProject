
output: testing.o cholesky.o ConjugateGradient.o Matrix.o SparseMatrix.o
	gcc testing.o cholesky.o ConjugateGradient.o Matrix.o SparseMatrix.o -O0 -o output -lm

testing.o: testing.c
	gcc -c testing.c -O0

cholesky.o: cholesky.c cholesky.h
	gcc -c cholesky.c -O0

ConjugateGradient.o: ConjugateGradient.c ConjugateGradient.h
	gcc -c ConjugateGradient.c -O0

Matrix.o: Matrix.c Matrix.h
	gcc -c Matrix.c -O0

clean:
	rm *.o output