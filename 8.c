#include<stdio.h>
#include<mpi.h>

int main( int argc, char* argv[])
{
	int rank, numproc;
	double a[100], b[100], isum=0.0, gsum;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numproc);
	
	for(int i=0; i<100; i++)
		a[i] = b[i] = 1.0;
		
	printf("Process %d is computing the dot product \n",rank);
	
	for(int i=0;i<100; i++)
		isum += a[i] * b[i];
	printf("\n Partial Sum for Process %d is %f\n",rank,isum);
	MPI_Reduce(&isum,&gsum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	
	if(rank==0)
		printf("\n The global sum is %f\n",gsum);
		
	MPI_Finalize();
}
