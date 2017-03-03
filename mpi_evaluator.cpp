#include "mpi_evaluator.h"
#include "const.h"

void scatter(const int n, double* scatter_values, int &n_local, double* &local_values, int source_rank, const MPI_Comm comm){

int MYRANK;
    int MYSIZE;
    MPI_Comm_rank(comm, &MYRANK);
    MPI_Comm_size(comm, &MYSIZE);
    int p = MYSIZE;
    int i,j;
    int r = n%p;
    int n_local_counter = 0;
    int n_local_counter2;
    

    //Implementation
    //if (MYRANK == source_rank){
    if (MYRANK == source_rank){
        for (i=0;i<MYSIZE;i++)
        {
            if (i < r)
            {
                n_local = (n/p)+1;
            }
            else
            {
                n_local = (n/p);
            }

            local_values = (double*)malloc(n_local*sizeof(double));
            for (j = 0; j < n_local; j++)
            {
                local_values[j]=scatter_values[n_local_counter+j];
                
            }
                //MPI_Send(&x, 1, MPI_DOUBLE, i, 0,communicator);
            MPI_Send(local_values, n_local, MPI_DOUBLE, i, 0, comm);
            n_local_counter = n_local_counter+ n_local;

        }
    }
        

        //MPI_Recv(&x, 1, MPI_DOUBLE, source_Rank, 0, communicator, MPI_STATUS_IGNORE);
        if (MYRANK < r)
            {
                n_local = (n/p)+1;
                n_local_counter2 = MYRANK*n_local;
            }
            else
            {
                n_local = (n/p);
                n_local_counter2 = r*(n_local+1)+(MYRANK-r)*n_local;
            }

            local_values = (double*)malloc(n_local*sizeof(double));
            for (j = 0; j < n_local; j++)
            {
                local_values[j]=scatter_values[n_local_counter2+j];
                
            }
        MPI_Recv(local_values, n_local2, MPI_DOUBLE, 0, 0, comm, MPI_STATUS_IGNORE);
        n_local_counter2 = n_local_counter2+ n_local;

    

 }   

double broadcast(double x, int source_rank, const MPI_Comm comm){
	int MYRANK;
    int MYSIZE;
    MPI_Comm_rank(comm, &MYRANK);
    MPI_Comm_size(comm, &MYSIZE);
    int count = 1;

    //Implementation
    if (MYRANK == source_rank){
        int i;
        for (i=0;i<MYSIZE;i++)
        {
            if (i != MYRANK)
            {
                //MPI_Send(&x, 1, MPI_DOUBLE, i, 0,communicator);
                MPI_Send(&value, count, MPI_DOUBLE, i, 0, comm);
            }

        }
    }
    else{
        //MPI_Recv(&x, 1, MPI_DOUBLE, source_Rank, 0, communicator, MPI_STATUS_IGNORE);
        MPI_Recv(&value, count, MPI_DOUBLE, 0, 0, comm, MPI_STATUS_IGNORE);
    }
    return 0;
}
void parallel_prefix(const int n, const double* values, double* prefix_results, const int OP, const MPI_Comm comm){
    //Implementation

}

double mpi_poly_evaluator(const double x, const int n, const double* constants, const MPI_Comm comm){
    //Implementation

    return 0;

    MPI_SEND(start, count, datatype, dest, tag, comm)