#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>

typedef struct {
    double *values;
    int *column_indices;
    int *row_pointers;
} CSR;

CSR CSRcreate(int size,double sparisty);//生成CSR矩阵
int validateCSR(CSR matrix, int size);//验证CSR矩阵