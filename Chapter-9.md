1. 分块矩阵
   $$
   \left(
   	\begin{array}{ccc}
   	
   		A_{00} & A_{01} & ... & ... \\
       
   		A_{10} & A_{11} & ... & ... \\
       
   		A_{20} & A_{21} & ... & ... \\
       
   	\end{array}
   \right)
   $$
   其中$A_{ij}$是$m * m$阶矩阵，

   (a) 请写出构造一个数据类型的子程序，使得新数据类型可以发送和接受小块矩阵$A_{00}$,并且可以一次性发送和接受$A_{00}$和$A_{20}$;

   (b) 如果只是发送$A_{00}$和$A_{20}$，是否还有其他构造数据类型的方法？如果有怎么构造？

```c
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
            MPI_Send(&matrix, 1, A_another_both, RECEIVER, 0, MPI_COMM_WORLD);              // the third para could be :A_zero,A_both,A_another_both
            printf("\n\n\n");
            break;
        }
        case RECEIVER:
        {
            // Receive the message
            int received[ROW][COLUMN] = {0};
            MPI_Recv(&received, 1, A_another_both, SENDER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // the third para is the same with function Send()
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
```

2. 设结构{int m[3]; float a[2]; char c[5];} 定义的数组为x[10]，如果将进程0长度为10的数组x发送给进程1，请写一个程序以验证。

```c
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
```

3. 假设分块下三角矩阵的对角块矩阵都是$m * m$阶的下三角矩阵，构造一个下三角矩阵的数据类型，使得这个数据类型可以用于传送这个矩阵的连续多个对角块矩阵。

```c
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
```

