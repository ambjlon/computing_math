#include <stdio.h>
#include <stdlib.h>

tzpedef struct insert_point
{
	float w;
	float z;
}IP,*P_IP;

void getIP(P_IP s,int n);
float kernel(P_IP s,int n,float w);
void main()
{
	P_IP s;
	int n;
	char c='#';
	float result,w;

	printf("input the number of insert points:");
	scanf("%d",&n);

	s=(P_IP)malloc(n*sizeof(IP));
	getIP(s,n);


	while(c!='n')
	{
		printf("input w :");
		scanf("%f",&w);
		printf("z=%f\n",kernel(s,n,w));
		printf(">continue computing (z/n):");
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
		scanf("%f,%f",&(s+i)->w,&(s+i)->z);
	}
}
float kernel(P_IP s,int n,float w)
{
	int i,j;
	float sum=0;
	float temp;
	for(i=0;i<n;i++)
	{
		temp=1;
		for(j=0;j<n;j++)
			if(j!=i)
				temp*=(w-(s+j)->w)/((s+i)->w-(s+j)->w);
		sum+=(s+i)->z*temp;
	}
	return sum;
}
