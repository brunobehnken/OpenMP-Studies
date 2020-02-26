#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *arq;
    long unsigned int n, elem, count = 0;
    long unsigned int *vec, *sorted_vec;
    long unsigned int  i, j;

    arq = fopen("vec.txt","r");
    fscanf(arq,"%lu",&n);
    vec = malloc(n * sizeof(long));
    sorted_vec = malloc(n * sizeof(long));
    for (i = 0; i < n; i++) {
        fscanf(arq, "%lu", &vec[i]);
    }
    fclose(arq);
    for (i = 0; i < n; i++) {
        elem = vec[i];
        for (j = 0; j < n; j++) {
            if (vec[j] < elem) {
                count += 1;
            }
        }
        sorted_vec[count] = elem;
        count = 0;
    }
    arq = fopen("output.txt","w+");
    for (i = 0; i < n; i++) {
        fprintf(arq,"%lu\n",sorted_vec[i]);
    }
    return 0;
}