#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 1024
#define M 1024
#define X 799
#define Y 799

// #define TAM 8
// #define M 10
// #define X 3
// #define Y 3

double temp[TAM][TAM], mat[TAM][TAM];

void sor(void) {
	int	i,j,k;

	for (k = 0; k < M; k++) {
		for (i = 1; i < TAM - 1; i++) {  // casas "pretas"
			j = (i%2) ? 1 : 2;
			for(; j < TAM - 1; j+=2) {
				if (i == X && j == Y) continue;
				temp[i][j] = 0.25*(mat[i-1][j] + mat[i+1][j] + mat[i][j-1] + mat[i][j+1]);
			}
		}
		memcpy(mat, temp, sizeof(mat));

		for (i = 2; i < TAM - 1; i++) {  // casas "brancas"
			j = (i%2) ? 2 : 1;
			for(; j < TAM - 1; j+=2) {
				if (i == X && j == Y) continue;
				temp[i][j] = 0.25*(mat[i-1][j] + mat[i+1][j] + mat[i][j-1] + mat[i][j+1]);
			}
		}
		memcpy(mat, temp, sizeof(mat));
	}
}

void initialize_matrix() {
	int i, j;

	for (i = 0; i < TAM; i++) {
		for(j = 0; j < TAM; j++)
			mat[i][j] = 20;
	}
	mat[X][Y] = 100;
	memcpy(temp, mat, sizeof(mat));
}

void print_matrix() {
	int i,j;

	for (i = 0; i < TAM; i++) {
		for(j = 0; j < TAM; j++)
			printf("[%d][%d] = %f, ",i, j, mat[i][j]);
		printf("\n");
	}
}

int main(int argc, char const *argv[]) {
	initialize_matrix();
	sor();
	print_matrix();
	return 0;
}