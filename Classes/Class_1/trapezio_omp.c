#include <stdio.h>
#include <math.h>
// #include "mpi.h"             /* Funções e definições MPI.  */
#include <omp.h>

double f(double x) {
        double return_val;
        return_val = exp(x);
        return return_val;
}

int main(int argc, char** argv) { 
    int meu_ranque;          /* O ranque do meu processo     */
    int p;                   /* O número de processos        */
    double a = 0.0;          /* Limite esquerdo              */
    double b = 1.0;          /* Limite direito               */
    long int n = 1000000000; /* Número de trapezóides        */
    double x,h;              /* x e h, a base do trapezoide  */
    double integral;         /* Integral de cada processo    */
    double total;            /* Integral total               */
    int origem;              /* Processo enviando a integral */
    int destino = 0;         /* Todas as mensagens vão para 0*/
    int etiq = 3;            /* Uma etiqueta qualquer        */
    // MPI_Status info;         /* Necessário para MPI_Recv     */
    double inicio, fim;
          
    /* Permite ao sistema iniciar o  MPI */
    // MPI_Init(&argc, &argv);
    /* Pega o ranque do meu processo */
    // MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    /* Encontra quantos processos estão ativos */
    // MPI_Comm_size(MPI_COMM_WORLD, &p);
       
    // inicio = MPI_Wtime();

    h = (b - a)/n;   /* h é o mesmo para todos os processos */

    /* O processo 0 calcula o valor inicial da sua integral */

    integral = (f(a) + f(b))/2.0;

    /* Cada processo calcula a integral aprox. sobre n/p trapézios*/ 

    // for (x =  a + h*meu_ranque; x < b ; x += p*h) {
    //      integral += f(x);
    //     }
    // integral = integral*h;

    /* O processo 0 recebe e soma as integrais parciais calculadas por cada processo */

    int root = 2;
    // MPI_Allreduce(&integral,&total,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);

    (void) omp_set_num_threads(4);
    #pragma omp parallel default(none) reduction(+:integral) shared(a,n,h)
    {
        // tid = omp_get_thread_num();
        int x;
        for (x = 1; x < n-1 ; x++) {
             integral += f(a + x*h);
            }
    }
    integral = integral*h;

/*    if (meu_ranque == 0) { 
        total = integral; 
        for (origem = 1; origem < p; origem++) { 
             MPI_Recv(&integral, 1, MPI_DOUBLE, origem, etiq, MPI_COMM_WORLD, &info);
             total += integral; 
            }
    } else {
        MPI_Send(&integral, 1, MPI_DOUBLE, destino, etiq, MPI_COMM_WORLD);
          }
*/
    /* Imprime o resultado */
    // fim = MPI_Wtime();

//    if (meu_ranque == 0){
        printf("Com n = %ld trapezoides, a estimativa \n", n);
        printf("da integral de %lf até %lf = %lf \n", a, b, total);

  	// printf("tempo =%2.2f \n", fim-inicio);
//        }

    /* Termina o MPI */
    // MPI_Finalize();        
} /* main */

