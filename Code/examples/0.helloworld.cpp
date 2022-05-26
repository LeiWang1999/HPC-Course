#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char * argv []) {
    int my_id, num_procs;
    int name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Get_processor_name(processor_name, &name_len);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    cout << "Hello World ! This is " << processor_name
         << " thread " << my_id << " of " << num_procs
         << endl;

    MPI_Finalize();
    return 0;
}
