/*1.全选主元GUASS消去,可处理任何形状矩阵.
  2.动态实现,处理大型矩阵无空间浪费.
  3.在浮点数处理时不完善.
   Written by ChenJianglong  10.29*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
	int rank;
	int row;
}Coordinate,*PCoordinate;

void print(float *p,int m,int n);
void swap(float *p,int m,int n,PCoordinate init,PCoordinate max);
void main(void)
{
	int m,n;
	int i,k,j,q,t;
	float *p;
	float temp;
	PCoordinate init,max;
	init=(PCoordinate)malloc(sizeof(Coordinate));
	max=(PCoordinate)malloc(sizeof(Coordinate));

	printf("in put rank and row in proper oder:");
	scanf("%d%d",&m,&n);
	p = (float *)malloc((m*n)*sizeof(float));
	printf("in put the matrix:\n");
    for(i=0;i<=m*n-1;i++)
		scanf("%f",p+i);
    
	printf("the matrix you set is:\n");
	print(p,m,n);

    for(k=0;k<=m-2;k++)
	{
		float Max=fabs(*(p+k*n+k));
		int r,c;
		for(q=k;q<=m-1;q++)
	    for(t=k;t<=n-1;t++)
		{
         if(fabs(*(p+q*n+t))>=Max)
		 {
			 Max=fabs(*(p+q*n+t));
			 r=q;
		     c=t;
		 }
		}
		if(Max==0)
			break;
		init->rank=init->row=k;
		max->rank=r;
		max->row=c;
		swap(p,m,n,init,max);
		for(i=k+1;i<=m-1;i++)
		{
			temp=-*(p+i*n+k)/(*(p+k*n+k));
			for(j=i*n+k;j<=(i+1)*n-1;j++)
				*(p+j)+=*(p+j-(i-k)*n)*temp;
		}
   /* print(p,m,n);*/
	}

    printf("After Guass the matrix is:\n");
	print(p,m,n);
}

void print(float *p,int m,int n)
{
	int i;
	for(i=0;i<=m*n-1;i++)
	{
		printf("%8f ",*(p+i));
		if((i+1)%n==0)
			printf("\n");
	}
	printf("\n");
}

void swap(float *p,int m,int n,PCoordinate init,PCoordinate max)
{
	int i;
	float temp;
	for(i=0;i<=n-1;i++)
	{
     temp=*(p+max->rank*n+i);
     *(p+max->rank*n+i)=*(p+init->rank*n+i);
     *(p+init->rank*n+i)=temp;
	}
	for(i=0;i<=m-1;i++)
	{
	 temp=*(p+i*n+init->rank);
     *(p+i*n+init->rank)=*(p+i*n+max->row);
	 *(p+i*n+max->row)=temp;
	}
}
