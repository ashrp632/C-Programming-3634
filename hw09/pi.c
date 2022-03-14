#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(int argc, char **argv){

    int nthreads = atoi(argv[1]);
    omp_set_num_threads(nthreads);
    long long int H = 0;
    long long int N = strtod(argv[2], NULL);
    int i = 0;
    double tic, toc;
    double elapsed = 0;
    
    tic = omp_get_wtime();
    struct drand48_data seed;
#pragma omp parallel
    {
      srand48_r(omp_get_thread_num(), &seed);
      for(i=1;i<N;++i){
        double x; 
        drand48_r(&seed,&x);
        double y;
        drand48_r(&seed,&y);
        H += (x*x+y*y<1);
      }

    }
    toc = omp_get_wtime();
    elapsed = (toc-tic);

    printf("N = %lld\n", N);
    printf("pi ~ %17.15lf\n", H*(4.)/N);
    printf("elapsed ~ %lg s\n", elapsed);
    printf("threads = %d\n",nthreads);
}

