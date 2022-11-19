#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <omp.h>
#include <stdbool.h>


char tempMat[6][7] = {{'C','C','C','C','C','C','C'},{'C','C','C','C','C','C','C'},{'C','C','H','H','H','C','C'},{'C','C','H','H','H','C','C'},{'C','C','H','H','H','C','C'},{'C','C','C','C','C','C','C'}};
int roomTemp[10][6][7];

void init_mat(){
    for(int i = 0; i < 10; i++){
        for (int j = 0; j < 6; j++){
            for (int k = 0; i < 7; j++){
                roomTemp[i][j][k] = -1;
            }
            
        }
    }
}
void printMat(){
    
    int i,j,k;
    for(k = 0; k < 10; k++){
        for(i =0; i<6; i++){
            for(j =0; j<7; j++){
                printf("%3d, ",roomTemp[k][i][j]);
            }
            printf("\n");
        }printf("\n");
    }
    
}

void* validMat(void *arg){
    int tempCount =0;
    int i,j,k;
    while(tempCount < 42){
        tempCount =0;  
        for(k =0; k< 2; k++){
            for(i = 0; i < 6; i++){
                for(j = 0; j < 7; j++){
                    if(roomTemp[k][i][j] >-1){
                        tempCount++;
                    }
                }
            }
        }
    }
    return NULL;
}

void* defineTemp(void *arg){
    int i,j;
    int k = (int)arg;
    srand(time(NULL));
    while (1){
        i = rand()%6;
        j= rand()%7;
        if(tempMat[i][j] == 67){
            roomTemp[k][i][j] = rand()%61;
        }else{
            roomTemp[k][i][j] = rand()%41 + 60;
        }
    }
    return NULL; 
}

void heatEQ(){
    int i,j,k;
    #pragma omp parallel for private(i,j,k) shared (*roomTemp)
    for(k = 0; k<10 ; k++){
        for(i = 0; i<6; i++){
            for(j = 0; j <7; j++){
                roomTemp[k+1][i][j] = 0.02 *(roomTemp[k][i+1][j] + roomTemp[k][i-1][j] + roomTemp[k][i][j+1]+ roomTemp[k][i][j-1]-4*roomTemp[k][i][j]) + roomTemp[k][i][j];
            }
        }
    }
     
}

int main(int argc, char *argv[]){
    int nthreads = atoi(argv[1]);
    pthread_t tid[nthreads];
    pthread_t master; 
    int i,j =0;
    int err;

    i = 0;
    while(i < nthreads) {
            err = pthread_create(&(tid[i]), NULL, &defineTemp, (void*) j);
            //err2 = pthread_create(&(tid[i]), NULL, &defineTemp, NULL);
            if (err != 0)
                printf("\ncan't create thread :[%s]", strerror(err));
            i++;
    }
    err = pthread_create(&(master), NULL, &validMat, NULL);
    if (err != 0)
                printf("\ncan't create thread :[%s]", strerror(err));
    pthread_join(master, NULL);
    pthread_cancel(master);
    for(i =0; i< nthreads; i++)pthread_cancel(tid[i]);


    #ifdef _OPENMP
        omp_set_num_threads(thread_num);
    #endif
    heatEQ();
    printMat();
    return 0;
}
