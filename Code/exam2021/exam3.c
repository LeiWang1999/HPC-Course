#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"



/**
 * @brief solution of problem3
 * @details This program is meant to be run with 2 processes: a sender and a
 * receiver. This program uses API::MPI_Type_create_struct to construct the 
 * datatype of struct;
 * 
 * Usage: mpicc exam3.c -o exam3 & mpirun -n 2 ./exam3
 **/

struct datatype{
    int m[3];
    float a[2];
    char c[5];
};


void rand_generate_datatype(struct datatype data[]){
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 3; j++)
            data[i].m[j] =  i;
        for(int j = 0; j < 2; j++)
            data[i].a[j] = 1.0 + i;
        for(int j = 0; j < 5; j++)
            data[i].c[j] = 'a' + i;
    }
}
void print_datatype(struct datatype data[]){
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 3; j++)
            printf("%2d ", data[i].m[j]);
        for(int j = 0; j < 2; j++)
            printf("%5.2f ", data[i].a[j]);
        for(int j = 0; j < 5; j++)
            printf("%c ", data[i].c[j]);
        printf("\n");
    }
}

void create_datatype(MPI_Datatype *new) {
    int lens[3] = {3, 2, 5};
    MPI_Aint disp[3];
    MPI_Datatype type[3] = {MPI_INT, MPI_FLOAT, MPI_CHAR};
    struct datatype tmp;
    MPI_Get_address(&tmp.m, &disp[0]);
    MPI_Get_address(&tmp.a, &disp[1]);
    MPI_Get_address(&tmp.c, &disp[2]);
    for(int i = 2; i >= 0; i--)
        disp[i] -= disp[0];
    MPI_Type_create_struct(3, lens, disp, type, new);
    MPI_Type_commit(new);
}


int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    // Get the number of processes and check only 2 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 2)
    {
        printf("This application is meant to be run with 2 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
    // Create the datatype
    MPI_Datatype new_struct;
    create_datatype(&new_struct);
    
    // Get my rank and do the job
    enum rank_roles { SENDER, RECEIVER };
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    switch(my_rank)
    {
        case SENDER:
        { 
            // Send the message
            struct datatype send[10] = {0};
            rand_generate_datatype(send);
            printf("MPI process %d sends values :\n", my_rank);
            print_datatype(send);
            MPI_Send(send, 10, new_struct, RECEIVER, 0, MPI_COMM_WORLD);
            printf("\n\n\n");
            break;
        }
        case RECEIVER:
        {
            // Receive the message
            struct datatype received[10] = {0};
            MPI_Recv(received, 10, new_struct, SENDER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("MPI process %d received values:\n", my_rank);
            print_datatype(received);
            break;
        }
    }
    MPI_Type_free(&new_struct);
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}