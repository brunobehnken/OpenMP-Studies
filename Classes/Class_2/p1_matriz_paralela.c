/* Programa 1:
 * Uma matriz 4xn deve ser preenchida com o valor 1.0
 * Cada uma das 4 threads deve preencher uma coluna */ 

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char const *argv[]) {
	// int j;
	int i, tid, n = 100000;
	float a[n][4];

	// for (i = 0; i < 4; i++) {
	// 	for (j = 0; i < n; j++)	{
	// 		a[i][j] = 1.0;
	// 	}
	// }

	omp_set_num_threads(4);
	#pragma omp parallel default(none) shared(a,n) private(tid,i)
	// for -> dividiria as repeticoes entre as threads
	// num_threads(4) -> equivale a omp_set_num_threads(4);
	// default(none) -> eh uma boa pratica de programacao pq te obriga a declarar se as variaveis sao private ou shared.
	// se vc nao colocar o default(none), todas as variaveis serao shared por padrao e isso pode dar erro.
	{
		tid = omp_get_thread_num();
		for (i = 0; i < n; i++)	{
			a[i][tid] = 1.0;
		}
	}

	for (i = 0; i < 4; i++)
		printf("%1.2f ",a[50][i]);
	printf("\n");
	return 0;
}