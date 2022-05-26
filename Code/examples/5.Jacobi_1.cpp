#include <mpi.h>
#include<fstream>
#include <sstream>
#include <iostream>


// determine the size of the array needing itering
#define N 100

// define the num of processes
#define X 4
// know the size of the array each process has
#define myarysize N / X

using namespace std;
int main(int argc, char* argv[])
{
    int n, myid, numprocs;
    int up, down;
    int opt;
    int i, j;

    // define the num of iterations
    int nsteps = 1000;


    double prev[myarysize + 2][N + 2], curr[myarysize + 2][N + 2], gather_arr[N][N + 2], temp[myarysize][N + 2];

    MPI_Datatype  onerow;
    MPI_Status  status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    // initialize all arrays

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N + 2; j++)
        {
            if (i < myarysize)
                temp[i][j] = 0;
            gather_arr[i][j] = 0;

        }
    }

    for (int i = 0; i < myarysize + 2; i++)
    {
        for (int j = 0; j < N + 2; j++)
        {
            prev[i][j] = 20.00;

        }

    }
    if (myid == 0)
    {
        for (int j = 0; j < N + 2; j++)
        {
            // 将第一行的大约三分之一到三分之二之间的位置设置为100，其他设置为20
            if (j > 0.3 * (N + 1) && j < 0.7 * (N + 1))
            {
                prev[0][j] = 100.00;
            }
        }
    }
    MPI_Type_contiguous(N + 2, MPI_DOUBLE, &onerow);

    MPI_Type_commit(&onerow);

    int begin_row = 1;
    int end_row = myarysize;
    for (n = 0; n < nsteps; n++)
    {
        if (myid < 3) {
            MPI_Send(&prev[myarysize][0], 1, onerow,
                     myid + 1, 1000, MPI_COMM_WORLD);
            MPI_Recv(&prev[myarysize + 1][0], 1, onerow,
                     myid + 1, 1000, MPI_COMM_WORLD, &status);

        }
        if (myid > 0) {
            MPI_Send(&prev[1][0], 1, onerow,
                     myid - 1, 1000, MPI_COMM_WORLD);
            MPI_Recv(&prev[0][0], 1, onerow,
                     myid - 1, 1000, MPI_COMM_WORLD, &status);
        }
        for (i = begin_row; i <= end_row; i++)
        {
            for (j = 1; j < N + 1; j++)
            {
                curr[i][j] = (prev[i][j + 1] + prev[i][j - 1] + prev[i - 1][j] + prev[i + 1][j]) * 0.25;

            }
        }
        for (i = begin_row; i <= end_row; i++)
        {
            for (j = 1; j < N + 1; j++)
            {

                prev[i][j] = curr[i][j];

            }
        }


    }/* 迭代结束*/

    // 用一个临时数组存放这些更新完的数组（去掉首行和末行，因为这两行是边界）
    for (int i = begin_row; i <= end_row; i++)
    {
        for (int j = 0; j < N + 2; j++)
        {

            temp[i - 1][j] = prev[i][j];
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Gather(&temp, myarysize * (N + 2), MPI_DOUBLE, &gather_arr, myarysize * (N + 2), MPI_DOUBLE, 0, MPI_COMM_WORLD);//需要单独在外面

    MPI_Type_free(&onerow);
    MPI_Finalize();
    if (myid == 0)
    {
        // output the result to the csv file
        std::ofstream myfile;
        myfile.open("finalTemperatures.csv");
        for (int p = 0; p < N + 2; p++)
        {
            for (int i = 0; i < N + 2; i++)
            {
                std::ostringstream out;
                out.precision(8);
                if (p == 0)
                {
                    if (i > 0.3 * (N + 1) && i < 0.7 * (N + 1))
                        myfile << "100" << ", ";
                    else
                        myfile << "20" << ", ";
                }
                else if (p == N + 1)
                    myfile << "20" << ", ";
                else
                {
                    out << gather_arr[p - 1][i];
                    std::string str = out.str(); //从流中取出字符串 数值现在存储在str中，等待格式化。
                    myfile << str << ", ";
                }
            }
            myfile << "\n";
        }
        myfile.close();

    }
    return 1;
}

