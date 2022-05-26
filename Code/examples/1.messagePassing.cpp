#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char * argv []) {
    char message [30];
    int my_id;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    if(0==my_id){
        //send message
        sprintf(message, "Hello, process 1!\n");
        MPI_Send(message, strlen(message), MPI_CHAR, 1 /* target */, 99, MPI_COMM_WORLD);
    }else if ( 1 == my_id){
        MPI_Status status;
        MPI_Recv(message, 30, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status);
        printf("received : %s", message);
    }

    MPI_Finalize();
    return 0;
}
