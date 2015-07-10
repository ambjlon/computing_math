//差商,打印差商表
//Written by ChenJianglong 2009.3.29
//ChenJianglong All the right reserve!
//the author is unaccountable to the similar progarms!
#include <stdio.h>
#include <stdlib.h>


typedef struct insert_point
{
	float x;
	float y;
}IP,*P_IP;

void getIP(P_IP s,int n);
float **kernel(P_IP s,int n);
void print_table(float **p,int n);
void free_mem(float **p,int n);


void main()
{
	int n;
	float **p;
	P_IP s;

	printf("input the number of insert points:");
	scanf("%d",&n);

	s=(P_IP)malloc(n*sizeof(IP));
	getIP(s,n);
	p=kernel(s,n);
	print_table(p,n);
	free_mem(p,n);
}

void getIP(P_IP s,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("intput the %dth point :",i+1);
		scanf("%f,%f",&(s+i)->x,&(s+i)->y);
	}
}


float **kernel(P_IP s,int n)
{
	int i,j;
	float **p;

	p=(float **)malloc(n*sizeof(float *));
	for(i=0;i<n;i++)
		*(p+i)=malloc(sizeof(float)*(i+1));

	for(i=0;i<n;i++)
		p[i][0]=(s+i)->y;

	for(i=1;i<n;i++)
		for(j=i;j<n;j++)
			p[j][i]=(p[j][i-1]-p[j-1][i-1])/((s+j)->x-(s+j-i)->x);
	return p;
}

void print_table(float **p,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<=i;j++)
			printf("f[%d..%d]=%f  ",i-j,i,p[i][j]);
		printf("\n");
	}
}
void free_mem(float **p,int n)
{
	int i;
	for(i=0;i<n;i++)
		free(*(p+i));
	free(p);
}
