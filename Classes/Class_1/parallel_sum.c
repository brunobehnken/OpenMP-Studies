#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define SUM_INIT 0

int main(int argc, char *argv[]) {
   int i, n = 25;
   int sum, a[n];
   int ref = SUM_INIT + (n-1)*n/2;
   (void) omp_set_num_threads(5);
   for (i=0; i<n; i++)    
          a[i] = i;
#pragma omp parallel
{
      #pragma omp single
          printf("Número de threads é %d\n", omp_get_num_threads());
    }

 sum = SUM_INIT;
   printf("Valor da soma antes da região paralela: %d\n",sum);

#pragma omp parallel default(none) shared(n,a,sum) //private(sum) // reduction(+:sum)
   {
   #pragma omp for schedule(static,3)
        for (i=0; i<n; i++)
          sum += a[i];
        printf("Soma dentro da regiao paralela: %d\n",sum);
   /*-- Fim da redução paralela  --*/
    }

   printf("Valor da soma depois da região paralela: %d\n",sum);
   printf("Verificação do resultado: soma = %d (deveria ser %d)\n",sum,ref);
   return(0);
}