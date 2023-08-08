#include "CSRcreate_bak.h"


CSR CSRcreate_bak(int size, double sparsity) {
    int non_zero_elements = round(size * size * sparsity);
    CSR matrix;

    matrix.values = (double *)malloc(sizeof(double) * non_zero_elements);
    matrix.column_indices = (int *)malloc(sizeof(int) * non_zero_elements);
    matrix.row_pointers = (int *)calloc(size + 1, sizeof(int));
    matrix.row_pointers[0] = 0;

    int *local_counts = (int *)calloc(size, sizeof(int)); // Temporary array to store non-zero counts for each row

    srand(time(NULL));  // Initialize global seed

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < size; i++) {
        double local_values[size];
        int local_indices[size];
        int local_count = 0;

        unsigned int seed = time(NULL) ^ omp_get_thread_num();

        for (int j = 0; j < size; j++) {
            if (rand_r(&seed) / (double)RAND_MAX < sparsity && local_count < size) {
                local_values[local_count] = (double)rand_r(&seed) / (double)RAND_MAX;
                local_indices[local_count] = j;
                local_count++;
            }
        }
        local_counts[i] = local_count;  // Store the count in the temporary array

        
        #pragma omp critical
        {
            int start_idx = matrix.row_pointers[i];
            for (int k = 0; k < local_count; k++) {
            matrix.values[start_idx + k] = local_values[k];
            matrix.column_indices[start_idx + k] = local_indices[k];
            }
        }

    }

    // Update the row_pointers based on the local_counts
    for (int i = 0; i < size; i++) {
        matrix.row_pointers[i + 1] = matrix.row_pointers[i] + local_counts[i];
    }

    free(local_counts);
    return matrix;
}


int validateCSR(CSR matrix, int size) {
    // 检查row_pointers
    if (matrix.row_pointers[0] != 0) {
        printf("Error: First element of row_pointers is not 0.\n");
        return 0;
    }

    for (int i = 1; i <= size; i++) {
        if (matrix.row_pointers[i] < matrix.row_pointers[i-1]) {
            printf("Error: row_pointers is not non-decreasing at index %d.\n", i);
            return 0;
        }
    }

    // 检查column_indices
    int totalElements = matrix.row_pointers[size];
    for (int i = 0; i < size; i++) {
        int startIdx = matrix.row_pointers[i];
        int endIdx = matrix.row_pointers[i+1];
        for (int j = startIdx; j < endIdx - 1; j++) {
            if (matrix.column_indices[j] >= matrix.column_indices[j+1] || matrix.column_indices[j] < 0 || matrix.column_indices[j] >= size) {
                printf("Error: column_indices are not unique or out of bounds for row %d ,column %d and %d.\n", i,matrix.column_indices[j],matrix.column_indices[j+1]);
                return 0;
            }
        }
    }

    return 1; // 结构正确返回1
}