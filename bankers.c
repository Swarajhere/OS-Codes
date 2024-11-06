#include<stdio.h>
#include<stdlib.h>

int main()
{
	int n,m;
	printf("Enter no of processes: ");
	scanf("%d",&n);
	printf("Enter no of resources: ");
	scanf("%d",&m);
	
	int alloc[n][m] , max[n][m] , need[n][m] ;
	int available[m] ;

	printf("resources alloted\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&alloc[i][j]);
		}
	}

	printf("max resources required\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&max[i][j]);
		}
	}

	printf("available resources\n");
	for(int i=0;i<m;i++)
	{
		scanf("%d",&available[i]);
	}
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)need[i][j] = max[i][j] - alloc[i][j] ;	
	}
	
	int done[n] ;
	for(int i=0;i<n;i++)done[i] = 0 ;
	int processSeq[n];
	int count = 0;
	int check[n] ;
	for(int i=0;i<n;i++)check[i] = -1 ;
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(count == check[j])
			{
				printf("The following system is not safe\n");
				return 0 ;
			}
			check[j] = count;
			if(done[j])continue ;
			int flag = 1 ;
			for(int k=0;k<m;k++)
			{
				if(need[j][k] > available[k])
				{
					flag = 0;
					break;
				}
			}
			if(flag)
			{
				processSeq[count] = j ;
				count++;
				done[j] = 1 ;
				for(int k=0;k<m;k++)
				{
					available[k] += alloc[j][k] ;
				}
			}
		}
		if(count==n)
		{
			printf("The safe sequence is:\n");
			for(int i=0;i<n;i++)
			{
				printf("%d ",processSeq[i]);
			}
			printf("\n");
			return 0;
		}
	}
}