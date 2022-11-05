#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define N 3
void imprimirMatriz(int **mat, int row, int col){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			printf("%d ",mat[i][j]);
		}
		printf("\n");
				        }

}

void llenarMatriz(int **mat, int row, int col){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			mat[i][j] = rand()%9+1;
		}
	}
}

int **generarMatriz(int row, int col){   
	int **mat;        
	mat = (int **)malloc(row*sizeof(int*)); 
	for (int i=0; i < row; i++) mat[i] = (int*)malloc(col*sizeof(int));
	return mat;
}

int **multiplicacion(int row, int col){
	int **matA, **matB, **matR;	    
	matA= generarMatriz(row, col);
	matB = generarMatriz(col, row);
	matR = generarMatriz(row, col);

	llenarMatriz(matA, row, col);
	llenarMatriz(matB, col, row);

	for(int i = 0; i < row; i++){
		for(int j = 0; j < row; j++){
			matR[i][j] = 0;
		}
	}

	imprimirMatriz(matA, row, col);
	printf("X\n");
	imprimirMatriz(matB, col, row);
	printf("=\n");

	int i, j,k;
	#pragma omp parallel for private(i,j,k) shared (matA,matB,matR)
	for( i = 0; i < row; i++){
		for(j = 0; j < row; j++){
			for( k = 0; k < col; k++){
				matR[i][j] += matA[i][k] * matB[k][j];
			}          
		}
	}

	return matR;
} 

int main(int argc, char** argv){
	int thread_num = 1;
	if (argc >1){
		thread_num = atoi(argv[1]);
	}

	srand(time(NULL));
			    
	int **matr;
	int filas = N;
	int columnas = N;

	
	#ifdef _OPENMP			          
		omp_set_num_threads(thread_num);
	#endif
	matr = multiplicacion(filas, columnas);
	imprimirMatriz(matr, filas, filas);
}
