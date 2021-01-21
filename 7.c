#include<stdio.h>
#include<string.h>
#include<mpi.h>
#define SIZE 30

int main(int argc,char* argv[])
{
	int rank,tag=0,root=3,temp,numproc;
	MPI_Status status;
	char msg[SIZE];
	strcpy(msg,"Hello!");
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numproc);
	if(rank==3)
	{
		for(temp=0; temp<numproc ; temp++)
		{
			if(temp!=3)
				MPI_Send(msg,SIZE,MPI_CHAR,temp,tag,MPI_COMM_WORLD);
		}
	}
	else {
		MPI_Recv(msg,SIZE,MPI_CHAR,root,tag,MPI_COMM_WORLD,&status);
		printf("Message %s received at Process %d from Process %d \n",msg,rank,root);
	     }
	     MPI_Finalize();
}
	    
