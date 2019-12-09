#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>
#ifdef _OPENMP
        #include <omp.h>
#endif

int main (int argc, char **argv){
        int rank,size;
        MPI_Status status;
        MPI_Init(&argc,&argv);

        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        MPI_Comm_size(MPI_COMM_WORLD,&size);
        int i, n;
        double dx, pi, x,y,result;
        double start, stop;
        n = atoi(argv[1]);

        dx = 1.0 / n;
        pi = 0.0;
        int chunk;
#ifdef _OPENMP
        chunk = n / omp_get_num_threads() / 100;
#endif


#pragma omp parallel private(x,y,result)
{
        result = 0.0;
#pragma omp  for schedule(dynamic,chunk) reduction(+:pi)
        for (i = rank; i < n; i+=size){
                x = i * dx;
                y = sqrt(1 - x * x);
                pi += y * dx;
        }

}

        MPI_Allreduce(&pi,&result,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);

//      printf("pi: %.12f\n",4*pi);
        MPI_Finalize();
        return 0;
}
