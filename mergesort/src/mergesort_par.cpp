#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include "omp.h"

int main() {
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Hello from thread %i!\n", thread_id);
    }


    return 0;
}