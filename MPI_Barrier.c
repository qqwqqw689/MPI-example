/**
 * @author RookieHPC
 * @brief Original source code at https://rookiehpc.org/mpi/docs/mpi_barrier/index.html
 **/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/**
 * @brief Illustrates how to use an MPI barrier.
 **/
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    printf("[MPI process %d] I start waiting on the barrier.\n", my_rank);
    MPI_Barrier(MPI_COMM_WORLD);
    // MPI_Barrier blocks all MPI processes in the given communicator until
    // they all call this routine.
    printf("[MPI process %d] I know all MPI processes have waited on the barrier.\n", my_rank);

    MPI_Finalize();

    return EXIT_SUCCESS;
}
