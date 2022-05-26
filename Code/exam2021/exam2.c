#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define M 3                             // A_{ij} is a M*M matrix
#define ROW 12                          // row and column of A
#define COLUMN 12           


/**
 * @brief solution of problem2
 * @details This program is meant to be run with 2 processes: a sender and a
 * receiver. This program uses API::MPI_Type_vector to construct the datatype 
 * of A_{00} and uses the new datatype and API::MPI_Type_create_struct to 
 * construct the datatype of A_{00} and A_{20};
 * For the seconde problem, this program uses API::MPI_Type_indexed to provide 
 * another solution of constructing datatype.
 * 
 * change the third param of API::send and API::recv into A_zero, A_both, A_another_both
 * Usage: mpicc exam2.c -o exam2 & mpirun -n 2 ./exam2
 **/


void print_matrix(int *matrix, int num_row, int num_col) {      // print matrix
    printf("\n");
    int p = 0;
    for(int i = 0; i < num_row; i++) {
        for(int j = 0; j < num_col; j++)
            printf("%2d ", matrix[p++]);
        printf("\n");
    }
}

void create_datatype(MPI_Datatype *A_zero, MPI_Datatype *A_both) {
    MPI_Type_vector(M, M, COLUMN, MPI_INT, A_zero);
    MPI_Type_commit(A_zero);
    int lens[2] = {1, 1}, int_size;
    MPI_Type_size(MPI_INT, &int_size);
    MPI_Aint disp[2] = {0, 2*M*ROW*int_size};
    MPI_Datatype type[2] = {*A_zero, *A_zero};
    MPI_Type_create_struct(2, lens, disp, type,A_both);
    MPI_Type_commit(A_both);
}

void create_another_datatype(MPI_Datatype *A_both_another) {   // 第二种方法，index扩展
    int lens[2*M];
    int disp[2*M];
    for(int i = 0; i < M; i++) {
        lens[i] = M;
        lens[M+i] = M;
        disp[i] = i * COLUMN;
        disp[M+i] = (2 * M + i) * COLUMN;    
    }
    MPI_Type_indexed(2*M, lens, disp, MPI_INT, A_both_another);
    MPI_Type_commit(A_both_another);
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
    MPI_Datatype A_zero, A_both, A_another_both;
    create_datatype(&A_zero, &A_both);
    create_another_datatype(&A_another_both);
    
    // Get my rank and do the job
    enum rank_roles { SENDER, RECEIVER };
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    switch(my_rank)
    {
        case SENDER:
        { 
            // Send the message
            int matrix[ROW][COLUMN] = {0};
            for(int i = 0; i < ROW; i++) { // generate matrix randomly 
               for(int j = 0; j < COLUMN; j++){
                   matrix[i][j] = rand()%100;
               }
                
            }
            printf("MPI process %d sends values :\n", my_rank);
            print_matrix(&matrix[0][0], ROW, COLUMN);
            MPI_Send(&matrix, 1, A_both, RECEIVER, 0, MPI_COMM_WORLD);              // the third para could be :A_zero,A_both,A_another_both
            printf("\n\n\n");
            break;
        }
        case RECEIVER:
        {
            // Receive the message
            int received[ROW][COLUMN] = {0};
            MPI_Recv(&received, 1, A_both, SENDER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // the third para is the same with function Send()
            printf("MPI process %d received values:\n", my_rank);
            print_matrix(&received[0][0], ROW, COLUMN);
            break;
        }
    }
    MPI_Type_free(&A_zero);
    MPI_Type_free(&A_both);
    MPI_Type_free(&A_another_both);
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}