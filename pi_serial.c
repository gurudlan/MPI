#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include<math.h>
#ifdef _OPENMP
        #include<omp.h>
#endif

int main(int argc, char **argv){

        int rank, size;
        int n,i;
        double dx, pi, x, y, vysl;

        n = atoi(argv[1]);
        dx = 1.0 / n;
        pi = 0.0;

        int chunk = n;

        MPI_Status status;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        MPI_Comm_size(MPI_COMM_WORLD,&size);


        #ifdef _OPENMP
                chunk = n / omp_get_num_threads() / 100;
        #endif

        //double start, stop;
        //start = MPI_Wtime();

        #pragma omp parallel private(x,y)
        {

        #pragma omp for schedule(dynamic, chunk) reduction(+:pi)
        for(i = rank; i < n; i+=size){
                x = i*dx;
                y = sqrt(1-x*x);
                pi += y*dx;
        }
        }


        MPI_Allreduce(&pi, &vysl, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

        //printf("pi: %.12f\n", 4*vysl);

        //stop = MPI_Wtime();
        //if(rank == 0){
               //printf("Potrebny cas na 1 spravu = %lf\n", (stop-start)/(2*50)*1e6);
        //}


        MPI_Finalize();
        return 0;
}
