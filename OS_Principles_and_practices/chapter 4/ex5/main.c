#include <stdio.h>
#include "thread.h"
#include <time.h>
#include <time.h>
#include <stdlib.h>


#define NUM 10
int step_i = 0;

int matrix1[10][10];
int matrix2[10][10];
int result[10][10];
/* */
void* multi(void* arg);
//static thread_t threads[NUM];

static pthread_t threads[NUM];
static pthread_attr_t attrs[NUM];



int main(int argc, char **argv){
    srand(time(NULL));
    int num = 10;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++){
            matrix1[i][j] = rand() % 10;
            matrix2[i][j] = rand() % 10;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_attr_init(&attrs[i]);
        pthread_create(&(threads[i]),&attrs[i], multi, &num);
    }
    
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    thread_join((threads[10]));

    return 0;
}

void* multi(void* arg){
    int i = step_i;

    int count = *(int*)arg;

    for (int j = 0; i < count; j++)
    {
        for (int k = 0; k < count; k++)
        {
            result[i][j] += matrix1[i][k] * matrix2[k][j];
        }   
    }
    return 0;
}