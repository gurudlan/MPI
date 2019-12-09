#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <omp.h>

int main (int argc, char **argv){
        int rank, size;
        double start, stop;

        int i,j,n;
        n = atoi(argv[1]);
        double dx, pi, x,y,result;

        dx = 1.0 / n;
        pi = 0.0;
        MPI_Init(&argc, &argv);

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        printf("Rank: %d Size: %d\n",rank,size);
        start = MPI_Wtime();
#pragma omp private (x,y)
{
#pragma omp for schedule(static, 8) reduction (+:pi)
        for (i = rank; i <= n; i+=size){
                x = i * dx;
                y = sqrt(1 - x * x);
                pi += y * dx;
        }

        stop = MPI_Wtime();

}
        printf ("Cas: %.21f s\n",(stop-start)*100);
        MPI_Finalize();
        return 0;
}
