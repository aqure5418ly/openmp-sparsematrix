#include "CSRcreate.h"

CSR CSRcreate_bak(int size, double sparisty) {
    int non_zero_elements = round(size * size * sparisty);
    CSR matrix;
    int alignment = 64; // Assuming a cache line size of 64 bytes for alignment.

    if (posix_memalign((void **)&matrix.values, alignment, sizeof(double) * non_zero_elements) ||
        posix_memalign((void **)&matrix.column_indices, alignment, sizeof(int) * non_zero_elements) ||
        posix_memalign((void **)&matrix.row_pointers, alignment, (size + 1) * sizeof(int))) {
        // Error handling for memory allocation failures
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    matrix.row_pointers[0] = 0; // Initialize the first value to 0.

    #pragma omp parallel for ordered schedule(static)
    for (int i = 0; i < size; i++) {
        int thread_id = omp_get_thread_num();
        unsigned int seed = time(NULL) ^ thread_id;
        int local_count = 0;
        double local_values[size];
        int local_indices[size];

        for (int j = 0; j < size; j++) {
            if (rand_r(&seed) / (double)RAND_MAX < sparisty && matrix.row_pointers[i] + local_count < non_zero_elements) {
                local_values[local_count] = (double)rand_r(&seed) / (double)RAND_MAX;
                local_indices[local_count] = j;
                local_count++;
            }
        }

        #pragma omp ordered
        {
            for (int k = 0; k < local_count; k++) {
                matrix.values[matrix.row_pointers[i] + k] = local_values[k];
                matrix.column_indices[matrix.row_pointers[i] + k] = local_indices[k];
            }
            matrix.row_pointers[i + 1] = matrix.row_pointers[i] + local_count;
        }
    }

    printf("Values: ");
    for (int i = 0; i < 10; i++) {
        printf("%f ", matrix.values[i]);
    }
    printf("\nColumn: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", matrix.column_indices[i]);
    }
    printf("\n");
    
    return matrix;
}