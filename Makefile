
output: testing.o cholesky.o ConjugateGradient.o Matrix.o SparseMatrix.o
	gcc testing.o cholesky.o ConjugateGradient.o Matrix.o SparseMatrix.o -o output -lm

testing.o: testing.c
	gcc -c testing.c

cholesky.o: cholesky.c cholesky.h
	gcc -c cholesky.c

ConjugateGradient.o: ConjugateGradient.c ConjugateGradient.h
	gcc -c ConjugateGradient.c

Matrix.o: Matrix.c Matrix.h
	gcc -c Matrix.c

clean:
	rm *.o output