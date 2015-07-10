/*用一维数组实现矩阵乘法
  written by ChenJianglong 2008.11.10*/
#include <stdio.h>
#include <stdlib.h>

void print(float *p,int m,int n);
void main(void)
{
	int m,n,b;
	int i,j,k,w;
	float *p,*q,*r;
	float sum;


	printf("in put the ln and col of the first matrix:\n");
	scanf("%d%d",&m,&n);
    printf("in put the ln and col of the second matrix:\n");
	scanf("%d%d",&n,&b);
    p=(float *)malloc((m*n-1)*sizeof(float));
	q=(float *)malloc((n*b-1)*sizeof(float));
	r=(float *)malloc((m*b-1)*sizeof(float));
	printf("in put the first matrix:\n");
	for(i=0;i<=m*n-1;i++)
		scanf("%f",p+i);
    printf("in put the second matrix:\n");
	for(i=0;i<=n*b-1;i++)
		scanf("%f",q+i);
   
    k=0;
	for(i=0;i<=m-1;i++)
    for(j=0;j<=b-1;j++)
	{
      sum=0;
	  for(w=0;w<=n-1;w++)
	  sum+=*(p+i*n+w)**(q+w*b+j);
	  *(r+k++)=sum;
	}
	print(r,m,b);

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
	putchar('\n');
}