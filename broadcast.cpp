#include <stdio.h>
#include <iostream>
#include <mpi.h>


double broadcast(double value, int source_rank, const MPI_Comm comm){
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
int main(int argc, char** argv){
    MPI_Init(NULL, NULL);
    int MYRANK;
    const MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_rank(comm, &MYRANK);
    double value;
    value = 9.0;
    if(MYRANK == 0)
    {
        std::cout << "The processor 0 is broadcasting data..."<< value;
        broadcast(value, 0,comm);
    }
    else {
        broadcast(value,0,comm);
        std::cout << "Processor" << MYRANK << "recieved data from the root processor";
    }
    MPI_Finalize();
}