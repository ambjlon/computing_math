#include <stdio.h>
#include <stdlib.h>

void print(float *p,int m,int n);
void main(void)
{
	int m,n;
	int i,k,j;
	float *p;
	float temp;

	printf("in put rank and row in proper oder:");
	scanf("%d%d",&m,&n);
	p = (float *)malloc((m*n)*sizeof(float));
	printf("in put the matrix:\n");
    for(i=0;i<=m*n-1;i++)
		scanf("%f",p+i);
    
	printf("the matrix you set is:\n");
	print(p,m,n);

    for(k=0;k<=m-2;k++)
		for(i=k+1;i<=m-1;i++)
		{
			temp=-*(p+i*n+k)/(*(p+k*n+k));
			for(j=i*n+k;j<=(i+1)*n-1;j++)
				*(p+j)+=*(p+j-(i-k)*n)*temp;
		}

    printf("After Guass the matrix is:\n");
	print(p,m,n);
}
void print(float *p,int m,int n)
{
	int i;
	for(i=0;i<=m*n-1;i++)
	{
		printf("%f ",*(p+i));
		if((i+1)%n==0)
			printf("\n");
	}
}
