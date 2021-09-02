#include <stdio.h>
#include "thread.h"
#include <time.h>
#include <time.h>
#include <stdlib.h>


#define NUM 4
/* */
void* multi(void* arg);


int main(int argc, char **argv){
    srand(time(NULL));
    int matrix1[NUM][NUM];
    int matrix2[NUM][NUM];

    int r1 = NUM, c1 = NUM, r2 = NUM, c2 = NUM;
    int i,j,k;

    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c1; j++){
            matrix1[i][j] = rand() % 10;
        }
    }

    for (int i = 0; i < r2; i++)
    {
        for (int j = 0; j < c2; j++){
            matrix2[i][j] = rand() % 10;
        }
    }

    /* Displaying Matrix 1 */
    for (i = 0; i < r1; i++){
        for(j = 0; j < c1; j++)
            printf("%d ",matrix1[i][j]);
        printf("\n");
    }

    printf("-----------------------------\n");

    /* Displaying Matrix 2 */
    for (i = 0; i < r1; i++){
        for(j = 0; j < c1; j++)
            printf("%d ",matrix1[i][j]);
        printf("\n");
    }

    pthread_t *threads;
    threads = (pthread_t*)malloc(c1*r2*sizeof(pthread_t));

    int count = 0;
    int *data = NULL;

    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++){
            data = (int *)malloc((20)*sizeof(int));
            data[0]=c1;

            for (k = 0; k < c1; k++)
            {
                data[k+1] = matrix1[i][k];
            }

            for (k = 0; k < c1; k++)
            {
                data[k+c1+1] = matrix2[k][j];
            }
            pthread_create(&threads[count++], NULL, multi, (void*)(data));
            
        }
    }
    
    printf("Result : \n");

    for(int i = 0; i < NUM * NUM; i++){
        void *k;
        pthread_join(threads[i], &k);

        int *p = (int *)k;
        printf("%d ", *p);
        if((i+1)%c2 == 0) printf("\n");
    }

    free(threads);

    return 0;
}

void *multi(void* arg){

    int *data = (int*)arg;
    int k = 0, i = 0;

    int x = data[0];

    for (i = 1; i <= x; i++)
    {
        k+=data[i]*data[i+x];
    }

    int *p = (int*)malloc(sizeof(int));
    *p = k;
    
    pthread_exit(p);
}