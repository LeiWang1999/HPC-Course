1. 用MPI\_SEND和MPI\_RECV实现MPI\_ALLTOALL的并行数据传输方法与程序；

```c
void myAlltoAll(const void * sendbuf, int sendcount, MPI_Datatype sendbyte, void * recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm){
  int rank,size;
  int type_size;
  MPI_Type_size(sendType, &type_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  
  for(int i = 0; i < size; ++i){
    if(i == rank){
      memcpy(sendbuf+i*sendcount*type_size, recvbuf + i*recvcount*type_size, sendcount*type_size);
      continue;
    }
    MPI_Send(sendbuf+i*sendcount*type_size, sendcount, sendtype,i,0,MPI_COMM_WORLD);
    MPI_Recv(recvbuf+i*recvcount*type_size, recvcount, recvtype,i,0,MPI_COMM_WORLD);
  }
  return;
}
```

2. 假设数组x的长度n=mp，证明：MPI\_Bcast=MPI_Scater+MPI\_Allgather

懒得证明了，显而易见 : )

祝考试顺利～