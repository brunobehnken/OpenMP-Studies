#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
  int nthreads, tid;
   #pragma omp parallel shared(nthreads, tid) num_threads(16)
   {
   /* Obtém o número da thread  */
   tid = omp_get_thread_num();
   /* Apenas as thread master faz isto */
   if (tid == 0) {
        nthreads = omp_get_num_threads();
         printf("Número de threads = %d\n", nthreads);
       }
   printf("Alô mundo da thread = %d\n", tid);
    } /* Todas as threads se juntam à thread master e terminam */
}