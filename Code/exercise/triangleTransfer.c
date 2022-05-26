#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define M 3                             // A_{ij} is a M*M matrix
#define ROW 12                          // row and column of A
#define COLUMN 12


void randomCreateTriangleMatrix(int * matrix, int row, int col){
    int p = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j, ++p) {
            if(j<=i){
                matrix[p] = rand()%100;
            }else{
                matrix[p] = 0;
            }
        }
    }
}

void print_matrix(int *matrix, int num_row, int num_col) {      // print matrix
    printf("\n");
    int p = 0;
    for(int i = 0; i < num_row; i++) {
        for(int j = 0; j < num_col; j++)
            printf("%2d ", matrix[p++]);
        printf("\n");
    }
}

void create_datatype(MPI_Datatype * TriangleType) {
    /*
     * 拆成边长为2的小三角形
     * */
    MPI_Datatype smallTriangleType;
    int small_lens[2] = {1, 2};
    int small_disp[2] = {0,ROW};
    int triangleNum = ROW/2;
    MPI_Type_indexed(2, small_lens, small_disp, MPI_INT, &smallTriangleType);
    MPI_Type_commit(&smallTriangleType);
    MPI_Datatype type[triangleNum];
    for (int i = 0; i < triangleNum; ++i) {
        type[i] = smallTriangleType;
    }
    int big_lens[triangleNum];
    MPI_Aint big_disp[triangleNum];
    int int_size;
    MPI_Type_size(MPI_INT, &int_size);
    for (int i = 0; i < triangleNum; ++i) {
        big_lens[i] = 1;
        big_disp[i] = (i*2*ROW+i*2)*int_size;
    }
    MPI_Type_create_struct(triangleNum, big_lens, big_disp, type, TriangleType);
    MPI_Type_commit(TriangleType);
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
    MPI_Datatype TriangleType;
    create_datatype(&TriangleType);

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
            randomCreateTriangleMatrix(&matrix[0][0], ROW, COLUMN);
            printf("MPI process %d sends values :\n", my_rank);
            print_matrix(&matrix[0][0], ROW, COLUMN);
            MPI_Send(&matrix, 1, TriangleType, RECEIVER, 0, MPI_COMM_WORLD);              // the third para could be :A_zero,A_both,A_another_both
            printf("\n\n\n");
            break;
        }
        case RECEIVER:
        {
            // Receive the message
            int received[ROW][COLUMN] = {0};
            MPI_Recv(&received, 1, TriangleType, SENDER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // the third para is the same with function Send()
            printf("MPI process %d received values:\n", my_rank);
            print_matrix(&received[0][0], ROW, COLUMN);
            break;
        }
    }
    MPI_Type_free(&TriangleType);
    MPI_Finalize();

    return EXIT_SUCCESS;
}