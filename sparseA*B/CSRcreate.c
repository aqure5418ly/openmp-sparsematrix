#include "CSRcreate.h"

/// @brief ����CSR��ʽ��ϡ�����
/// @param size Ŀ������С
/// @param sparisty �������ϡ���
/// @return 
CSR CSRcreate(int size,double sparisty)
{
    int non_zero_elements = round(size * size * sparisty);
    CSR matrix;
    matrix.values = (double *)malloc(sizeof(double) * non_zero_elements);
    matrix.column_indices = (int *)malloc(sizeof(int) * non_zero_elements);
    matrix.row_pointers = (int *)calloc(size + 1, sizeof(int));
    
    srand(time(NULL));//����ȫ������
    int count = 0;
    #pragma omp parallel for private(count)
    for(int i = 0; i < size; i++)
    {
        int thread_id = omp_get_thread_num();
        unsigned int seed = time(NULL) ^ thread_id; // Ϊÿ���߳����ò�ͬ������
        count = 0;
        for(int j = 0; j < size; j++)
        {
            if(i == 0)
            {
                if(rand_r(&seed) / (double)RAND_MAX < sparisty && count < non_zero_elements-1)
                {                     
                    matrix.values[count] = (double)rand_r(&seed) / (double)RAND_MAX;
                    matrix.column_indices[count] = j;
                    count++;              
                }
            }
            else
            {
                if(rand_r(&seed) / (double)RAND_MAX < sparisty && matrix.row_pointers[i-1]+count < non_zero_elements-1)
                {
                    count++;  
                    matrix.values[matrix.row_pointers[i-1]+count] = (double)rand_r(&seed) / (double)RAND_MAX;
                    matrix.column_indices[matrix.row_pointers[i-1]+count] = j;              
                }
            }
        }
        matrix.row_pointers[i] = matrix.row_pointers[i-1]+count;        
    }
    printf("Values: ");
    for(int i = 0;i<10;i++)
    {
        printf("%f ",matrix.values[i]);
    }
    printf("\nColumn: ");
    for(int i = 0;i<10;i++)
    {
        printf("%d ",matrix.column_indices[i]);
    }
    printf("\n");
    return matrix;
}