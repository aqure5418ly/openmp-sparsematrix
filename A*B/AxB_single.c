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
    srand(time(NULL)); // 设置随机种子

   start = omp_get_wtime();  // 获取开始时间
    for (int i = 0; i < SIZE; i++) {
        B[i] = (double)rand() / (double)RAND_MAX; // 生成0到1之间的随机双精度浮点数
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = (double)rand() / (double)RAND_MAX; // 生成0到1之间的随机双精度浮点数
        }
    }
    for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                C[i][j] = A[i][j] * B[j];
            }
        }
    end = omp_get_wtime();
    // 测试输出一些元素，看是否初始化成功
    printf("A[0][0] = %f, B[0] = %f\n", A[0][0], B[0]);
    printf("A[2047][2047] = %f, B[2047] = %f\n", A[2047][2047], B[2047]);
    printf("C[0][0] = %f\n", C[0][0]);
    printf("C[2047][2047] = %f\n", C[2047][2047]);
    printf("Time = %.6f\n", end - start);  // 打印运行时间

    return 0;
}
