#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void merge(int a[],int x1, int y1, int x2, int y2)
{
	int p = x1;
	int q = x2;
	int k = 0;
	int temp[1000];
	while(p <= y1 && q <= y2){
		if(a[p] < a[q])
			temp[k++] = a[p++];
		else
			temp[k++] = a[q++];
	}
	
	while( p<=y1)
		temp[k++] = a[p++];
	while(q<=y2)
		temp[k++] = a[q++];
		
	for(int i=x1, j=0; i<=y2; i++,j++)
		a[i] = temp[j];
}

void mergesort(int a[], int p, int q)
{
	int mid;
	if(p<q){
		mid = (p+q)/2;
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				mergesort(a,p,mid);
			}
			#pragma omp section
			{
				mergesort(a,mid+1,q);
			}
		}
		merge(a,p,mid,mid+1,q);
		}
}

int main()
{
	int n;
	
	printf("\n Enter the number of elements \n");
	scanf("%d",&n);
	
	int a[n];
	for(int i=0; i<n; i++)
		a[i] = rand()%100;
	
	printf("\n Unsorted Array is \n");
	for(int i=0; i<n; i++)
		printf("%d \t",a[i]);
		
	mergesort(a,0,n-1);
	
	printf("\n Sorted Array: \n");
	for(int i=0; i<n;i++)
		printf("%d \t",a[i]);
	printf("\n");
	
}
