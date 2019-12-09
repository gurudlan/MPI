#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (int argc, char **argv){
        int rank, size;

        MPI_Status status;
        MPI_Init(&argc, &argv);

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        int  namelen;
        char proc_name [MPI_MAX_PROCESSOR_NAME];
        MPI_Get_processor_name(proc_name, &namelen);

        printf("Ja som %d z %d, bezim na %s\n", rank , size, proc_name);
        int number = 16,i;
        double start, stop;

        start = MPI_Wtime();
        for (i = 0; i < 50; i++){
                if (!rank){
                        MPI_Send(&number,1,MPI_INT,1, 0,MPI_COMM_WORLD);
                        MPI_Recv(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
                        //printf("Prijata sprava rank: %d cislo: %d\n", rank, number);
                }
                else{
                        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
                        //printf("Prijata sprava rank: %d cislo: %d\n",rank, number);
                        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                }
        }
        stop = MPI_Wtime();

        if (rank){
                printf("Cas: %.2lf s\n",(stop-start)*100);
        }

        MPI_Finalize();
        return 0;
}
