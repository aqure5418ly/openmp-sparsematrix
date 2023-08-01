#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SIZE 2048

int main() {
    double A[SIZE][SIZE];
    double B[SIZE];
    double C[SIZE][SIZE];
    double start,end;
    srand(time(NULL)); // �����������

   start = omp_get_wtime();  // ��ȡ��ʼʱ��
    for (int i = 0; i < SIZE; i++) {
        B[i] = (double)rand() / (double)RAND_MAX; // ����0��1֮������˫���ȸ�����
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = (double)rand() / (double)RAND_MAX; // ����0��1֮������˫���ȸ�����
        }
    }
    for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                C[i][j] = A[i][j] * B[j];
            }
        }
    end = omp_get_wtime();
    // �������һЩԪ�أ����Ƿ��ʼ���ɹ�
    printf("A[0][0] = %f, B[0] = %f\n", A[0][0], B[0]);
    printf("A[2047][2047] = %f, B[2047] = %f\n", A[2047][2047], B[2047]);
    printf("C[0][0] = %f\n", C[0][0]);
    printf("C[2047][2047] = %f\n", C[2047][2047]);
    printf("Time = %.6f\n", end - start);  // ��ӡ����ʱ��

    return 0;
}
