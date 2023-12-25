#include <stdio.h>
#include <mpi.h>

// [n1, n2), [ista, iend). 
void para_range(int n1, int n2, int nprocs, int irank, int &ista, int &iend)
{
  int iwork1;
  int iwork2;
  iwork1 = ( n2 - n1 ) / nprocs;
  iwork2 = ( ( n2 -n1 ) % nprocs );
  ista = irank*iwork1 + n1 + ((irank<iwork2) ? irank : iwork2);
  iend = ista + iwork1;
  if(iwork2 > irank) iend +=1;
}

int main (int argc, char *argv[])
{
    int rank, comm_size;
    int nn = 1000;
    int a[nn];
    for(int i=0; i<1000; i++)
        a[i]=i;
    int i, sum, ssum, m, n;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    para_range(0,nn,comm_size,rank,m,n);
    sum = 0;
    for (int i = m; i < n; i++)
    {
        sum += a[i];
    }
    MPI_Reduce(&sum,&ssum,1,MPI_INTEGER,MPI_SUM,0,MPI_COMM_WORLD);
    // int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, 
    // MPI_Op op, int root, MPI_Comm comm)
    // sendbuf address of send buffer
    // count number of elements in send buffer
    // MPI_SUM - Sums the elements.
    // MPI_Reduce combines the elements provided in the input buffer of each process
    // in the group, using the operation op, and returns the combined value in the output
    // buffer of the process with rank root.
    
    if(rank==0)
    {
        sum = ssum;
        printf("sum=%d\n",sum);
    }
    MPI_Finalize();

    return 0;
}
