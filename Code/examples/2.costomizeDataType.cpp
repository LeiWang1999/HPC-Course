#include <iostream>
#include <mpi.h>

using namespace std;

typedef struct {double value; char str;} customizeDataType;

int main(int argc, char * argv []) {
    int p, myid, len[3] = {1,1,1}, i;
    MPI_Comm mycomm;
    customizeDataType tst[3];
    MPI_Datatype _new, type[2] = {MPI_DOUBLE, MPI_CHAR};
    MPI_Aint disp[3], size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_dup(MPI_COMM_WORLD, &mycomm);
    MPI_Comm_rank(mycomm, &myid);
    MPI_Comm_size(mycomm, &p);

    if(0 == myid)
        for (i = 0; i < 3; ++i) {
            tst[i].value = 1.0;
            tst[i].str = 'a';
        }
    cout << "\nThe Process " << myid << " of " << p << "is running \n" ;


    return 0;
}
