#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double sinet[1000];
int primet[1000];

void prime_table(int pnum)
{
	int i,j,p,prime;
	i = 2,p=0;
	while(p<pnum) //Keeping track of size of the array
	{
		prime=1;
		for(j=2;j<i;j++) // Checking if i has any factors
		{
			if((i%j)==0){
				prime=0;
				break;	
			}
		} 
		
		
		if(prime){  // If i doesn't have any factors, add it to the prime table
			primet[p] = i;
			p = p+1;	
		}
		
		i = i+1; // Try the same procedure with the next value of i
	}
}

void sine_table(int snum)
{
	int i,j;
	double a,pi=3.14;
	for(i=0;i<snum;i++)
	{
		sinet[i] = 0.0;
		for(j=0;j<=i;j++){
			a = (double)(j)*pi/(double)(snum-1);
			sinet[i] += sin( a );
		}
	}
}

void main() {
	int size,z,y;
	printf("\n ENter the number of prime table & sine table values required. \n");
	scanf("%d",&size);
	
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			prime_table(size);
			printf("\n Prime Table: \n");
			for(y=0;y<size;y++)
				printf("%d \n",primet[y]);
		}
		#pragma omp section
		{
			sine_table(size);
			printf("\n Sine Table: \n");
			for(y=0;y<size;y++)
				printf("%lf \n",sinet[y]);
		}
	}
}
