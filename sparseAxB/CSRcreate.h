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

CSR CSRcreate(int size,double sparisty);//����CSR����
int validateCSR(CSR matrix, int size);//��֤CSR����