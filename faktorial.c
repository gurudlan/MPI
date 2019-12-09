#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>


int main (int argc, char **argv){
        int rank, size;
        srand(time(NULL));
        MPI_Status status;
        MPI_Init(&argc, &argv);

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        int fakt=1, n, i,vysl;

        n = atoi(argv[1]);

        for (i=rank+1; i <= n;i+=size){
                fakt *= i;
        }

        MPI_Allreduce(&fakt,&vysl, 1, MPI_INT,MPI_PROD,MPI_COMM_WORLD);

        printf("rank: %d fakt: %d vysl: %d\n",rank, fakt,vysl);

        MPI_Finalize();
        return 0;
}
