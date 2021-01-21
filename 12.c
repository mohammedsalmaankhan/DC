#include<stdio.h>
#include<mpi.h>
#include<time.h>
#include<stdlib.h>
int fun(int i){
	int square = i*i;
	return square;
}

int search(int a, int b, int c, int rank, int numproc)
{
	int res, i,j=-1;
	for(i=a+rank; 0<i && i<=b; i=i+numproc){
		res = fun(i);
		if(res==c){
			j=i;
			break;
		}
	}
	return j;
}
int main( int argc, char* argv[])
{
	int rank,numproc,A,B,C,j;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numproc);
	
	A=1,B=10,C=49;
	if(rank==0)
		printf("\n A:%d  B:%d  C:%d \n",A,B,C);
		
	double time1 = MPI_Wtime();
	j = search(A,B,C,rank,numproc);
	double time2 = time1 - MPI_Wtime();
	
	if (j!=-1 )
		printf("Process %d found J= %d.\n Therefore F(%d) = %d.\n Time Taken: %lf\n",rank,j,j,C,time2);
	
	MPI_Finalize();
}
