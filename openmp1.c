#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define M 3 
#define N 4 

int A[M][N] = { {0, 12, 13, 10},
                {54, 2, 3, 3},
                {0, 1, 1, 2} };

int B[N][M] = { {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9},
                {10, 11, 12} };

int C[M][M]; 

int main() {
    int i, j, k;

    omp_set_num_threads(2);

    #pragma omp parallel for private(j, k)
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
