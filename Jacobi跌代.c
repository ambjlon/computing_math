#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define IM 20 

float find_r(float **a,float *b,float *init,int n);
int main(void)
{
	int i,j,k;
	int n;
	float r;
	float **a;
	float *b;
	float *init;
	float sum;
	float tol=0.00001;
	printf("input n:\n");
	scanf("%d",&n);
    a=(float **)malloc(n*sizeof(float *));
	a[0]=(float *)malloc(n*n*sizeof(float));
	for(i=1;i<n;i++)
		a[i]=a[i-1]+n;
	b=(float *)malloc(n*sizeof(float));
	init=(float *)malloc(n*sizeof(float));
	printf("input a:\n");
	for(i=0;i<=n-1;i++)
		for(j=0;j<=n-1;j++)
			scanf("%f",&a[i][j]);
	printf("input b:\n");
	for(i=0;i<=n-1;i++)
	scanf("%f",&b[i]);
	printf("input init X :\n");
	for(i=0;i<n;i++)
		scanf("%f",&init[i]);
    
    i=0;
	r=find_r(a,b,init,n);
    while(i<IM&&r>=tol)
	{
      for(j=0;j<n;j++)
	  {
		  sum=0;
		  for(k=0;k<n;k++)
			  sum+=a[j][k]*init[k];
		  init[j]=-(sum-b[j])/a[j][j];
	  }
	  i++;
      r=find_r(a,b,init,n);
	}

	printf("total times:");
	printf("%d\n",i);
	printf("tol:");
	printf("%f\n",r);
	printf("RESULT:\n");
	for(i=0;i<n;i++)
		printf("%f\n",init[i]);
}
float find_r(float **a,float *b,float *init,int n)
{
	int i,j;
	float *r;
	float sum;
    r=(float *)malloc(n*sizeof(float));
    for(i=0;i<n;i++)
	{
		sum=0;
		for(j=0;j<n;j++)
		   sum=sum+a[i][j]*init[j];	
		r[i]=b[i]-sum;
	}
	sum=0;
	for(i=0;i<n;i++)
		sum+=r[i]*r[i];
	sum=sqrt(sum);
	free(r);
	return sum;
}
