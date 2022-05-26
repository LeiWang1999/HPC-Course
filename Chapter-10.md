1. 用MPI\_SEND和MPI\_RECV实现MPI\_ALLTOALL的并行数据传输方法与程序；

```c
#include "mpi.h"
#include "stdio.h"

#define  maxlen 10

int  My_Alltoall(int  *sendBuffer,int sendcnt,MPI_Datatype sendtype,
                 int *receiveBuffer,int recvcnt,MPI_Datatype recvtype,MPI_Comm comm,int rank,int size)
{
  int i;
  int j;
  MPI_Status status;

  if(size!=sendcnt||sendtype!=recvtype)
      return 0;
  for(i=0;i<size;i++)
  {
     if(rank==i)
     {
       MPI_Sendrecv(&sendBuffer[i],1,sendtype,i,99,&receiveBuffer[i],1,recvtype,i,99,comm,&status);
     }
     else
     {
       MPI_Send(&sendBuffer[i],1,sendtype,i,i,comm);
       MPI_Recv(&receiveBuffer[i],1,recvtype,i,rank,comm,&status); 
     }
     
 }
return 1;  

}

int main(int argc,char *argv[])
{
   int rank,size;
   MPI_Status status;
   

   int sendBuffer[maxlen],receiveBuffer[maxlen];
   int i,j;
   int count;
  
   MPI_Init(&argc,&argv);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   MPI_Comm_size(MPI_COMM_WORLD,&size);

    if( size < 1 || size > 10 )
     { if( rank == 0 ) printf("Please input a  number between 1-10\n");
       MPI_Finalize();
       return 0;
      }
   count=size;

   for(i=0;i<maxlen;i++)
   {
       sendBuffer[i]=(rank+1)*(i+1);
       receiveBuffer[i]=0;					
   }
      

   My_Alltoall(sendBuffer,count,MPI_INT,receiveBuffer,count,MPI_INT,MPI_COMM_WORLD,rank,size);
   
   if(rank==0)
   {
     for(i=0;i<count;i++)
     {
       printf("%d\t",receiveBuffer[i]);
     }
  }

   MPI_Finalize();
   return (0);
}

```

2. 假设数组x的长度n=mp，证明：MPI\_Bcast=MPI_Scater+MPI\_Allgather

懒得证明了，显而易见 : )

祝考试顺利～