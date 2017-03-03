#include <stdio.h>
#include <iostream>
#include <mpi.h>

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
    

        //MPI_Recv(&x, 1, MPI_DOUBLE, source_Rank, 0, communicator, MPI_STATUS_IGNORE);
        //MPI_Recv(&value, count, MPI_DOUBLE, 0, 0, comm, MPI_STATUS_IGNORE);
int main(int argc, char** argv){
    MPI_Init(NULL, NULL);
    //std::cout<<"i";
    int MYRANK;
    int localn;
    double* valuelocal; 
    const MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_rank(comm, &MYRANK);
    std::cout<<"rank is"<<MYRANK<<"\n";
    int n = 10;
    //double constants[8];
    double constants[10] = {7,8,7,3,5,1,0,9,3,2};
    int j;
    
    if(MYRANK == 0)
    {
        scatter(n, constants, localn, valuelocal, 0 ,comm);
        std::cout << "The processor 0 scatters values...";
        for (j = 0; j < n; j++){
            std::cout << constants[j] << "\t";
        }
        std::cout << "\n";
        
           
    }
    
        scatter(n, constants, localn, valuelocal, 0 ,comm);
        for (j = 0; j < localn; j++){
            std::cout << "The processor" << MYRANK << "recieves the scattered values..." << valuelocal[j] << "\n";
        }
        //std::cout << "Processor" << MYRANK << "recieved data from the root processor";
    
    //int MPI_Barrier(MPI_Comm comm);
    
    MPI_Finalize();

} 
    