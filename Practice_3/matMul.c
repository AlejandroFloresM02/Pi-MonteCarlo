#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 100

void matrixMult(int rowsA, int colA, int matC[rowsA][colB]){
	int suma = 0;
	int i,j,k; 


	

	#pragma omp parallel for shared(matA, matB, matC) private(i, j, k)
	for(i = 0; i < rowsA; i++){
		for(j =0;j < colB; j++){
			for(k =0; k < colA; k++){
				suma += matA[i][k] * matB[k][j];
			}
			matC[i][j] = suma; 
		}
	}
}
void printMat(int row, int col, int mat[row][c){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

int **generaMat(int row, int col){
	int **tempMat;
	tempMat = (int **)malloc(row*sizeof(int*));
	for(int i = 0; i < row; i++) tempMat[i] = (int*)malloc(columnas*sizeof(int));
	return matTemp;

}
int main(int argc, char** argv){

