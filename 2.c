#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main()
{
	int nrows,ncols,j;
	printf("Enter the number of rows followed by the number of columns\n");
	scanf("%d %d",&nrows,&ncols);
	int result[nrows],vector[ncols],matrix[nrows][ncols];
	
	for(int i=0;i<nrows;i++)
		for( j=0;j<ncols;j++)
			matrix[i][j] = i+j;
	
	for(int i=0;i<nrows;i++)
		result[i] = 0;
	
	for( j=0;j<ncols;j++)
		vector[j] = j;
		
	printf("Matrix is: \n");
	for(int i=0;i<nrows;i++){
		for(j=0;j<ncols;j++){
			printf("%d \t",matrix[i][j]);
		}
			printf("\n");
	}
	
	printf("\n Vector is: \n");
	for(j=0;j<ncols;j++)
		printf("%d \t",vector[j]);
		
	omp_set_num_threads(32);
	#pragma omp parallel private(j)
	for(int i=0;i<nrows;i++)
		for(j=0;j<ncols;j++)
			result[i] += matrix[i][j]*vector[j];
			
	printf("\nThe result is: \n");
	for(int i=0;i<nrows;i++)
		printf("%d \t",result[i]);
	 
}
