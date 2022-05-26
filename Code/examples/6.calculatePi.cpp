#include <iostream>
#include <mpi.h>

using namespace std;

double f(double x){
    return 4.0 / (1+ x*x);
}

int main(int argc, char * argv []) {
    int numprocs;
    int rank;
    int n = 1;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0){
        cout << "Please give n = " ;
        cin >> n;
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    double sum = 0;
    double wide = 1.0 / n;
    for (int i = rank; i < n; i+=numprocs) {
        double height = f(wide * ((double)i + 0.5));
        sum += height * wide;
    }
    double pi = 0.0;
    MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0){
        cout << "pi is approximately " << pi << endl;
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}
