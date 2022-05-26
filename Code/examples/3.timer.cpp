#include <iostream>
#include <mpi.h>
#include <ctime>
#include <unistd.h>
using namespace std;

int main(int argc, char * argv []) {

    MPI_Init(&argc, &argv);
    int my_id;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    int err = 0;
    double t1 = MPI_Wtime();
    double t2 = MPI_Wtime();
    if(t2-t1 > 0.1 || t2-t1 < 0.0){
        err++;
        fprintf(stderr, "Two successive calls to MPI_Wtime gave strange results : (%lf), (%lf) \n", t1, t2);
    }
    int i;
    for (i = 0; i < 10; ++i) {
        t1 = MPI_Wtime();
        sleep(1);
        t2 = MPI_Wtime();
        if(t2 - t1 >= (1.0-0.01) && t2-t1 <= 5.0) break;
        if(t2 - t1 > 5.0) i = 9;
    }
    if(i == 10){
        fprintf(stderr, "Timer around sleep(1) did not give 1 second; gave %f\n", t2-t1);
        ++err;
    }
    double tick = MPI_Wtick();
    if (tick > 1.0 || tick < 0.0){
        err++;
        fprintf(stderr, "MPI_Wtick gave a strange result: (%f)\n", tick);
    }
    fprintf(stdout, "Success in process %d\n", my_id);

    MPI_Finalize();
    return 0;
}
