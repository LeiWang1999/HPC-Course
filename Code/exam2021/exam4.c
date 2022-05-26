#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <string.h>

#define N 4                             // N processes
#define B 2                             // the basic data length


/**
 * @brief solution of problem4
 * @details This program is meant to be run with N processes: we use 
 * send and recv to finish the function of API::all_gather()
 * 
 * Usage: mpicc exam4.c -o exam4 & mpirun -n 4 ./exam4
 * 
 **/


void MY_Allgather(
    void *sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void *recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm
) {
    if(sendcount != recvcount || sendtype != recvtype)
        return;
    int elem_size, rank, world_size;
    MPI_Type_size(sendtype, &elem_size);
    MPI_Comm_size(comm, &world_size);
    MPI_Comm_rank(comm, &rank);
    
    int ssize = sendcount * elem_size;
    
    for(int i = 0; i < world_size; i++) {
        if(i == rank) {  
            for(int j = 0; j < world_size; j++) {
                if(j == i)
                    memcpy(recvbuf+ssize*j, sendbuf, ssize);
                else
                    printf("MPI process %d sends values to MPI process %d \n", i,j);
                    MPI_Send(sendbuf, sendcount, sendtype, j, i, comm);
            }
        } else {
            MPI_Recv(recvbuf+ssize*i, recvcount, recvtype, i, i, comm, MPI_STATUS_IGNORE);
        }
    }
}


int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
	int rank, size;
    int send[B], received[B*N];
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
    for(int i = 0; i < B; i++)
        send[i] = rank * B + i;

    MY_Allgather(send, B, MPI_INT, received, B, MPI_INT, MPI_COMM_WORLD);
	printf("MPI process[%d / %d] received values: %2d %2d %2d %2d %2d %2d %2d %2d\n", rank, size, 
           received[0], received[1], received[2], received[3], received[4], received[5], received[6], received[7]);
	MPI_Finalize();
	return EXIT_SUCCESS;
}