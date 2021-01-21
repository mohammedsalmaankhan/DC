#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char* argv[])
{
	int rank, count=0, numproc;
	long total = 10000;
	double x,y,z;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numproc);
	MPI_Status status;
	
	int rec[numproc];
	
	if(rank != 0 )
	{
		for( int i=0; i< total; i++)
		{
			x = ((double)rand())/RAND_MAX;
			y = ((double)rand())/RAND_MAX;
			z = x*x + y*y;
			
			if(z<=1)
				count++;
		}
		for(int j=0; j<numproc; j++)
			MPI_Send(&count,1,MPI_INT,0,10,MPI_COMM_WORLD);
	}
	else if(rank==0)
	{
		for(int j=0; j<numproc; j++)
			MPI_Recv(&rec[j],numproc,MPI_INT,MPI_ANY_SOURCE,10,MPI_COMM_WORLD,&status);
			
		int totalcount =0;
		for( int j=0; j<numproc; j++)
			totalcount+=rec[j];
			
		double pi =  (((double)(totalcount))/((double)total*(double)numproc))*4.0;
		printf("\n Calculated Value of pi is : %f \n",pi);
	}
	MPI_Finalize();
}
