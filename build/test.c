#include <cblas.h>
#include <stdio.h>

void main() {

    int i = 0;
    double A[6] = {1.0,2.0,1.0,-3.0,4.0,-1.0};         
    double B[6] = {1.0,2.0,1.0,-3.0,4.0,-1.0};  
    double C[9] = {.5,.5,.5,.5,.5,.5,.5,.5,.5}; 

    int M = 3; // row of A and C
    int N = 3; // col of B and C
    int K = 2; // col of A and row of B

    double alpha = 1.0;
    double beta = 0.0;

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, A, K, B, N, beta, C, N);

    for (i = 0; i < 9; i++) {
        printf("%lf ", C[i]);
    }
    printf("\n");
}