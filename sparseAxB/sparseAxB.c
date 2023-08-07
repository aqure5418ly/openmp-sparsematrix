#include "CSRcreate.h"

#define SIZE 2048  // 矩阵大小
#define SPARSITY 0.05  // 最大稀疏度
#define THREADS_NUM 16  // 线程数

int main()
{
    double start, end;
    double B[SIZE];
    double C[SIZE];
    omp_set_num_threads(THREADS_NUM);
    start = omp_get_wtime();  // 获取开始时间
    CSR matrix = CSRcreate(SIZE,SPARSITY); //创建稀疏矩阵A
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        unsigned int seed = time(NULL) ^ thread_id; // 为每个线程设置不同的种子
        
        #pragma omp for schedule(static)      //静态调度
        for (int i = 0; i < SIZE; ++i)     //创建向量B
        {
            B[i] = (double)rand_r(&seed) / (double)RAND_MAX;
        }
        
        #pragma omp for reduction(+:C[:SIZE]) schedule(dynamic)  //动态调度
        for (int i = 0;i < SIZE;i++)
        {
            double sum = 0.0;            
            for(int k = matrix.row_pointers[i];k<matrix.row_pointers[i+1];k++)
            {
                int j=matrix.column_indices[k];
                double value = matrix.values[k];
                C[i] += value * B[j];
            }
        }
    }
    end = omp_get_wtime();  // 获取结束时间
    //Print the sparse matrix in CSR format
    printf("Values: ");
    for (int i = 0; i < matrix.row_pointers[SIZE-1]; i++) {
        if(matrix.column_indices[i] == matrix.column_indices[0])
        {
            printf("%f ", matrix.values[i]);
        }
        
    }
    printf("\nRow pointers: ");
    for(int i = 0;i<5;i++)
    {
        printf("%d ", matrix.row_pointers[i]);
    }
    printf("%d ", matrix.row_pointers[SIZE-1]);
    printf("\nMatrix C:");
    printf("%f ",C[matrix.column_indices[0]]);
    printf("\n");
    printf("Time = %.6f\n", end - start);  // 打印运行时间
    free(matrix.values);
    free(matrix.column_indices);
    free(matrix.row_pointers);

    return 0;
}