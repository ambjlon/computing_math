//等距节点插值，可以按最佳插值方法进行计算
//Written by ChenJianglong 2009.4.5
//ChenJianglong All the right reserve!
//the author is unaccountable to the similar progarms!
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct insert_point
{
	float x;
	float y;
}IP,*P_IP;

int factorial(int k);
float lasttab(float t,float **p,int n);
float firsttab(float t,float **p,int n);
float **compute_table(P_IP s,int n);
void getIP(P_IP s,int n);
float bessel(float t,float **p,int n);
float string(float t,float **p,int n);
float jud_flag(P_IP s,float x,int n);
void print_table(float **p,int n);
int main()
{
	int n;
	float i,x;
	float **p;
	P_IP s;

	printf("input the number of inserted points:");
	scanf("%d",&n);

	s=(P_IP)malloc(n*sizeof(IP));
	getIP(s,n);

	p=compute_table(s,n);
	printf("TABLE:\n");
	printf("input x:");
	print_table(p,n);
	printf("\n\n");

	printf(">>input X :");
	scanf("%f",&x);

	i=jud_flag(s,x,n);
	
	printf("Compute result :");
	if(i>=2&&i<=3)
	{
		printf("%f\n",firsttab(i-2,p,n));
		return 0;
	}
	if(i>=4)
	{
		printf("%f\n",lasttab(i-4,p,n));
		return 0;
	}
	if(fabs(i)<=0.25&&fabs(i)!=-1)
	{
		printf("%f\n",string(fabs(i),p,n%2==1?n:n-1));
		return 0;
	}
	if(fabs(i)>0.25&&fabs(i)<=1)
	{
		printf("%f",bessel(fabs(i),p,n%2==0?n:n-1));
		return 0;
	}
	if(i=-1)
		printf("Cannot compute X!\n");
	return 0;
}
void getIP(P_IP s,int n,FILE *fp)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("intput the %dth point :",i+1);
		scanf("%f,%f",&(s+i)->x,&(s+i)->y);
	}
}
float **compute_table(P_IP s,int n)
{
	int i,j;
	float **p;
	p=(float **)malloc(sizeof(float *)*n);
	
	for(i=0;i<n;i++)
		*(p+i)=malloc(sizeof(float)*(i+1));

	for(i=0;i<n;i++)
		p[i][0]=(s+i)->y;

	for(i=1;i<n;i++)
		for(j=i;j<n;j++)
		p[j][i]=p[j][i-1]-p[j-1][i-1];
	return p;
}
float firsttab(float t,float **p,int n)
{
	int k,i;
	float sum=0;
	for(k=1;k<n;k++)
	{
		for(i=1;i<=k-1;i++)
			t*=(t-i);
		t/=factorial(k);
		sum+=(t*p[k][k]);
	}
	return p[0][0]+sum;
}
float lasttab(float t,float **p,int n)
{
	int k,i;
	float sum=0;
	float temp;
	for(k=1;k<n;k++)
	{
		temp=t;
		for(i=1;i<=k-1;i++)
			temp*=(temp-i);
		temp/=factorial(k);
		if(k%2)
			temp=-temp;
		sum+=(temp*p[n-1][k]);
	}
	return p[n-1][0]+sum;
}
float bessel(float t,float **p,int n)//n 是偶数
{
	int m,k,i;
	float sum=0,temp;
	m=n/2-1;

	for(k=0;k<=m;k++)
	{
		temp=t+k-1;
		for(i=1;i<=2*k-1;i++)
		temp*=(temp-i);
		temp/=factorial(2*k);
		if(k==0)
			temp=1;///// !!!!
		temp*=((t-0.5)/(2*k+1));//  1/2 is NO!!!!!!!!!!!!!!!
		sum+=(temp*p[k+m+1][2*k+1]);
	}
	for(k=1;k<=m;k++)
	{
		temp=t+k-1;
		for(i=1;i<=2*k-1;i++)
		temp*=(temp-i);
		temp/=factorial(2*k);
		sum+=(temp*(p[k+m][2*k]+p[k+m+1][2*k])/2);
	}
	return sum+(p[m][0]+p[m+1][0])/2;
}
float string(float t,float **p,int n)
{
	int m,k,i;
	float sum=0,temp;
	m=(n-1)/2;

	for(k=1;k<=m;k++)
	{
		temp=t+k-1;
		for(i=1;i<=2*k-2;i++)
		temp*=(temp-i);
		temp/=factorial(2*k-1);
		sum+=(temp*(p[k+m][2*k-1]+p[k+m-1][2*k-1])/2);
	}
	for(k=1;k<=m;k++)
	{
		temp=t+k-1;
		for(i=1;i<=2*k-2;i++)
		temp*=(temp-i);
		temp/=factorial(2*k-1);
		temp=temp*t/(2*k);
		sum+=(temp*p[k+m][2*k]);
	}
	return sum+p[m][0];
}
float jud_flag(P_IP s,float x,int n)
{
	int i;
	float space=(s+1)->x-s->x;
	for(i=0;i<n-1;i++)
		if(x>=(s+i)->x&&x<=(s+i+1)->x)
			break;
	if(i==n-1)
		return -1; //no function to be called
	if(i==0)
		return 2+(x-s->x)/space; //call firsttab function
	if(i==n-2)
		return 4+((s+n-1)->x-x)/space; //call lasttab function
	return (x-((s+i+1)->x-(s+i)->x)/2)/space;
}
int factorial(int k)
{
	int n=1,i;
	if(k==0)
		return 1;
	for(i=1;i<=k;i++)
		n*=i;
	return n;
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