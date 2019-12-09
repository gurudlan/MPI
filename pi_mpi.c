#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>


int main (int argc, char **argv){
        int rank, size;
        srand(time(NULL));
        MPI_Status status;
        MPI_Init(&argc, &argv);

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        int n,i;
        double dx, pi, x,y,result;

        n = atoi(argv[1]);

        dx = 1.0 / n;
        pi = 0.0;

        for (i = rank+1; i <= n; i+=size){
                x = i * dx;
                y = sqrt(1 - x * x);
                pi += y * dx;
        }

        MPI_Allreduce(&pi, &result,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);

        if (rank==0)
                printf("pi: %.12f\n",4*result);

        MPI_Finalize();
        return 0;
}
