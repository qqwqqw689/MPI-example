#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[])
{
    int rank, comm_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    for (int i = 0; i < 17; i++)
    {
        if (i%comm_size != rank) continue;

        printf("rank %i working on element %i\n", rank, i);

        // rest of work ...
    }

    MPI_Finalize();
}
