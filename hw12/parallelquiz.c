// Reduced version of parallelquiz.c for scalability studies

#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

// Declare functions that will be defined later
float logisticMap(float a,float r);
float logisticLimit(float a,float r);

int main(int argc, char **argv){
    if(argc != 3){
        fprintf(
            stderr,
            "You must provide two command line arguments: number of cores and array size\n"
        );
        return 1;
    }

    int nthreads = atoi(argv[1]);
    int N = atoi(argv[2]);

    if(nthreads > N){
        fprintf(
            stderr,
            "Number of threads exceeds array size (you probably put arguments in the wrong order)\n"
        );
        return 1;
    }

    omp_set_num_threads(nthreads);

    int n, i, temp;

    int *v = (int*) malloc(N*sizeof(int));
    float *z = (float*) malloc(N*sizeof(float));

    float a0 = 0.2;
    float r = 3.6;

    //////////////////////////////////////////
    // PUT THREAD INITIALIZATION BLOCK HERE //
    //////////////////////////////////////////

    // Loop B
    // Propagate value from v[0] to all entries of v
    v[0] = 7;
#pragma omp parallel for
    for(n=1;n<N;++n){
        v[n] = v[0];
    }

    // Loop H
    // In z[n], store an approximate periodic point of the logistic map with parameter 4*n/N
#pragma omp parallel for
    for(n=0;n<N;++n){
        z[n] = logisticLimit(a0,4.*n/N);
    }

    // Loop I
    // In v[n], store 1 if n is prime, 0 otherwise
#pragma omp parallel for private(i)
    for(n=0;n<N;++n){
        if(n<2){
            v[n] = 0;
            continue;
        }
        v[n] = 1;
        for(i=2;i<=n/2;++i){
            if(n%i==0){
                v[n] = 0;
                break;
            }
        }
    }

    // Loop J
    // In v[n], store the sum of the first n odd numbers
#pragma omp parallel for
    for(n=0;n<N;++n){
        v[n] = n*n;
    }

    free(v);
    free(z);

    return 0;
}

/*
   DO NOT MODIFY THESE FUNCTIONS
   You should think of them as library functions
   that are outside of your control.
 */

// Perform one logistic map iteration
float logisticMap(float a,float r){
    return a*(1-a)*r;
}

// Iterate 1000 times to find an approximate periodic point
float logisticLimit(float a,float r){
    for(int i=0;i<1000;++i){
        a = logisticMap(a,r);
    }
    return a;
}

