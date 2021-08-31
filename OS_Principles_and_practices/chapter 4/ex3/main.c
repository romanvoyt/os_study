#include <stdio.h>
#include "thread.h"
#include <time.h>

#define NTHREADS 1000

/* Purpose of the program is to calculate execution time of creating 1000 threads */

static thread_t threads[NTHREADS];

int main(int argc, char **argv){
    int i = 0;
    clock_t start = clock();

    for(i = 0; i < NTHREADS; i++){
        thread_create(&threads[i], thread_exit, 0);
        printf("Thread #%d is created \n", i);
    }

    clock_t end = clock();
    double finalTime = (double)(end - start)/CLOCKS_PER_SEC;
    printf("final time = %f\n", finalTime);
}