#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char * argv []) {
    int value;
    int size;
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    do{
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        if(rank == 0){
            fprintf(stderr, "Please give me a number:");
            scanf("%d",&value);
            fprintf(stderr, "%d read %d from system input \n", rank, value);
            /* first rank start to send*/
            if(size > 1){
                fprintf(stderr, "%d send %d to %d \n", rank, value, rank + 1);
                MPI_Send(&value, 1, MPI_INT, rank + 1, 99, MPI_COMM_WORLD);
            }
        }else{
            MPI_Status status;
            MPI_Recv(&value, 1, MPI_INT, rank - 1, 99, MPI_COMM_WORLD, &status);
            fprintf(stderr, "%d receive %d from %d \n", rank, value, rank - 1);
            if(rank < size){
                MPI_Send(&value, 1, MPI_INT, rank + 1, 99, MPI_COMM_WORLD);
                fprintf(stderr, "%d send %d to %d \n", rank, value, rank + 1);
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }while(value > 0);
    MPI_Finalize();
    return 0;
}
