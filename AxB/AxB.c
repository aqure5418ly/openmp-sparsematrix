#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SIZE 2048 //�����С
#define THREADS_NUM 16 //�߳���
int main() {
    double A[SIZE][SIZE];
    double B[SIZE];
    double C[SIZE];
    double start, end;

    // ΪA,B,C��������ڴ沢�����ڴ����
    if (posix_memalign((void**)&B, 64, SIZE * sizeof(double)) != 0 ||
        posix_memalign((void**)&C, 64, SIZE * sizeof(double)) != 0 ||
        posix_memalign((void**)&A, 64, SIZE * sizeof(double*)) != 0) 
    {  
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < SIZE; i++) {
        if (posix_memalign((void**)&(A[i]), 32, SIZE * sizeof(double)) != 0) {  // Allocate rows for A
            printf("Memory allocation for A row %d failed\n", i);
            exit(1);
        }
    }
    
    srand(time(NULL)); // ����ȫ���������
    omp_set_num_threads(THREADS_NUM);
    start = omp_get_wtime();  // ��ȡ��ʼʱ��
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        unsigned int seed = time(NULL) ^ thread_id; // Ϊÿ���߳����ò�ͬ������
        #pragma omp for
        for (int i = 0; i < SIZE; i++) {
            B[i] = (double)rand_r(&seed) / (double)RAND_MAX; // ����0��1֮������˫���ȸ�����
            for (int j = 0; j < SIZE; j++) {
                A[i][j] = (double)rand_r(&seed) / (double)RAND_MAX; // ����0��1֮������˫���ȸ�����
            }
        }
    }

    #pragma omp parallel for schedule(static)
        for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    C[i] += A[i][j] * B[j];
                }
            }
    end = omp_get_wtime();  // ��ȡ����ʱ��

    // �������һЩԪ�أ����Ƿ��ʼ���ɹ�
        
    printf("A[0][0] = %f, B[0] = %f\n", A[0][0], B[0]);
    printf("A[2047][2047] = %f, B[2047] = %f\n", A[2047][2047], B[2047]);
    for(int i = 0;i < SIZE;i++)
    {
        printf("%f ",A[i][1]);
    }
    printf("C[0] = %f\n", C[0]);
    printf("C[2047] = %f\n", C[2047]);
    printf("Time = %.6f\n", end - start);  // ��ӡ����ʱ��

    return 0;

}