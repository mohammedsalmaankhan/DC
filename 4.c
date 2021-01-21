#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main()
{
	int fact1=1,fact2=1,n,i;
	printf("\n Enter a number to compute its factorial");
	scanf("%d",&n);
	
	#pragma omp parallel for private(n)
	for(i=1;i<=n;i++)
		fact1 *= i;
		
	printf("\n Factorial of when n is private: %d \n",fact1);

	#pragma omp parallel for firstprivate(n)
	for(i=1;i<=n;i++)
		fact2 *= i;
		
	printf("\n Factorial of when n is firstprivate: %d \n",fact2);
}

