#include<stdio.h>


void f(int (*a)[2][2])
{
	int i,j;
	for(i=0; i<2; i++)
	{
		for(j=0; j<2; j++)
		{
			printf("%d ",(*a)[i][j]); 			//二维
			//printf("%d ",(*a)[j]); 	//一维
		}
		printf("\n");
	}
}

void hell(int a[2][2])
{}

int main()
{
	int a[2][2] = {{1,223},{323,4}};//二维
	//int a[4] = {1,2,3,45}; //一维
	//f(&a);
	hell(a);
}
