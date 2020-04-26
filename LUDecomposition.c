#include<stdio.h>
#include<string.h>


void LUDecompose(double A[][4], int n, double b[4]) {
	double lower[n][n], upper[n][n];
	double z[10]={0};
	double x[10]={0}; 
    memset(lower, 0, sizeof(lower)); 
    memset(upper, 0, sizeof(upper));
	for (int i = 0; i < n; i++) { 
  
        // Upper Triangular 
        for (int k = i; k < n; k++) { 
  
            // Summation of L(i, j) * U(j, k) 
            int sum = 0; 
            for (int j = 0; j < i; j++) 
                sum += (lower[i][j] * upper[j][k]); 
  
            // Evaluating U(i, k) 
            upper[i][k] = A[i][k] - sum; 
        } 
  
        // Lower Triangular 
        for (int k = i; k < n; k++) { 
            if (i == k) 
                lower[i][i] = 1; // Diagonal as 1 
            else { 
  
                // Summation of L(k, j) * U(j, i) 
                int sum = 0; 
                for (int j = 0; j < i; j++) 
                    sum += (lower[k][j] * upper[j][i]); 
  
                // Evaluating L(k, i) 
                lower[k][i] = (A[k][i] - sum) / upper[i][i]; 
            } 
        } 
    }

    for (int i = 0; i < n; i++) { 
        // Lower 
        for (int j = 0; j < n; j++) 
           printf("%f ", lower[i][j]);  
        printf(" ") ;
  
        // Upper 
        for (int j = 0; j < n; j++) 
           printf("%f ", upper[i][j]);  
        printf("\n"); 
    }
}

void LUSolve(){

}

int main() {
	double a[4][4] = { { 4, 12, 10, 10 }, 
                       { 12, 6, 7, 4 }, 
                       { 2, 8, 10, 11 },
                       { 7, 10, 6, 12} };
    double b[4] = {166, 112, 161, 173};
  
    LUDecompose(a, 4, b); 
    return 0;
}