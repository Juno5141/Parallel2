#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 3
#define N 4
#define NUM_THREADS 8

int A[M][N] = { {5, 7, 4, 4},
                {25, 2, 1, 1},
                {93, 1, 2, 3} };

int B[N][M] = { {4, 1, 5},
                {2, 7, 0},
                {1, 2, 7},
                {2, 5, 4} };

int C[M][M]; 

void *multiply(void *arg) {
    int thread_id = *((int*)arg);
    int i, j, k;

    int start_row = thread_id * M / NUM_THREADS;
    int end_row = (thread_id + 1) * M / NUM_THREADS;

    for (i = start_row; i < end_row; i++) {
        for (j = 0; j < M; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i, j;

    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, multiply, (void*)&thread_ids[i]);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
