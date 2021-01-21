#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>
#define K 4
int points[100][2],size,cluster_count[K],cluster[K][2]={{75,25},{25,25},{25,75},{75,75}};

double calcdist(int x1, int y1, int x2,  int y2)
{
	double dx = x2 - x1, dy = y2 - y1; 
	double dist = (double)(sqrt(dx*dx - dy*dy));
	return dist;
}

void makepoints()
{
	int i,j;
	#pragma omp parallel for num_threads(4)
	for(i=0;i<size;i++){
		points[i][0] = rand()%100; // x points
		points[i][1] = rand()%100; // y points
	}
	printf(" \nThe data points are:\n");
	for(i=0;i<size;i++)
		printf("%d  %d \n",points[i][0],points[i][1]);
	
	for(i=0;i<K;i++)
		cluster_count[i] = 0; // Initially there are 0 points in each cluster
}

void classify()
{
	int cluster_index,cdist,min_dist,i,j;
	#pragma omp parallel for num_threads(4) private(cluster_index, j , i, cdist, min_dist)
	for(i=0;i<size;i++)
	{
		cluster_index = -1;
		min_dist=999;
		cdist = 0;
		for(j=0;j<K;j++)
		{
			cdist = calcdist(points[i][0],points[i][1],cluster[j][0],cluster[j][1]);
			
			if(cdist<min_dist)
			{
				min_dist = cdist;
				cluster_index = j;

			}
		}
		printf("\n Point (%d,%d) belongs to cluster (%d,%d)",points[i][0],points[i][1],cluster[cluster_index][0],cluster[cluster_index][1]);
		cluster_count[cluster_index]++;
		
	}
}

void main(){
	    printf("Max threads:%d\n",omp_get_max_threads());
	    printf("Enter number of points");
	    scanf("%d",&size);
	    makepoints();
	    
	    classify();
	    
	    int i=0;
	    printf("\nCounts\n");
	    while(i<K)
	        printf("%d->%d\n",i,cluster_count[i++]);
}
