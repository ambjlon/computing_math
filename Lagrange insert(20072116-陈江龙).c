//lagrange ²åÖµ
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
float kernel(P_IP s,int n,float x);
void main()
{
	P_IP s;
	int n;
	char c='#';
	float result,x;

	printf("input the number of insert points:");
	scanf("%d",&n);

	s=(P_IP)malloc(n*sizeof(IP));
	getIP(s,n);


	while(c!='n')
	{
		printf("input x :");
		scanf("%f",&x);
		printf("y=%f\n",kernel(s,n,x));
		printf(">continue computing (y/n):");
		getchar(c);
		getchar();
	}
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
float kernel(P_IP s,int n,float x)
{
	int i,j;
	float sum=0;
	float temp;
	for(i=0;i<n;i++)
	{
		temp=1;
		for(j=0;j<n;j++)
			if(j!=i)
				temp*=(x-(s+j)->x)/((s+i)->x-(s+j)->x);
		sum+=(s+i)->y*temp;
	}
	return sum;
}
