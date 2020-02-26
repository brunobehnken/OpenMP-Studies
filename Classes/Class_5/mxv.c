#include <stdio.h>
#include <stdlib.h>

void mxv(int m, int n, double * restrict a, double * restrict b, double * restrict c) {
   int i, j;

   #pragma omp parallel for schedule(static) default(shared) private(i,j) num_threads(32)
   for (i=0; i<m; i++) {
      a[i] = 0.0;
      for (j=0; j<n; j++)
         a[i] += b[i*n+j]*c[j];
   } /*-- End of omp parallel for --*/
}

int main(int argc, char *argv[]) {
   double *a,*b,*c;
   int i, j, m, n;

   printf("Please give m and n: ");
   scanf("%d %d",&m,&n);
   printf("\n");

   if ((a = (double *)malloc(m*sizeof(double))) == NULL) perror("memory allocation for a");
   if ((c = (double *)malloc(n*sizeof(double))) == NULL) perror("memory allocation for c");
   if ((b = (double *)malloc(m*n*sizeof(double))) == NULL) perror("memory allocation for b");

   printf("Initializing matrix B and vector c\n");
   #pragma omp parallel for schedule(static) default(shared) private(i,j) num_threads(32)
      for (j=0; j<n; j++)
         c[j] = 2.0;
   #pragma omp parallel for schedule(static) default(shared) private(i,j) num_threads(32)
      for (i=0; i<m; i++)
         for (j=0; j<n; j++)
            b[i*n+j] = i;

   printf("Executing mxv function for m = %d n = %d\n",m,n);
   mxv(m, n, a, b, c);

   free(a);free(b);free(c);
   return(0);
}
