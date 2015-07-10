//打印 p.68 表2.2.1 [数值计算方法 下  张法勇]
//run in VC++ 6.0
//Written by ChenJianglong 2009.4.16
//ChenJianglong All the rights reserve!
//the author is unaccountable to the similar progarms!
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct insert_point
{
	float x;
	float y;
}IP,*P_IP;

void getIP(P_IP s,int n);
void free_mem(float **p,int n);
float **init_threediagMatrix(int n);
void kernel_1(float **a,P_IP s,int n);
float kernel_2(float x,P_IP s,int n);
float comput_M4(float x);
float lagrange(P_IP s,int n,float x);
void copy(P_IP c,P_IP s,int n);

void main()
{
	FILE *fp;
	int i;
	int n=11;//number of inserted points
	float x;
	float **p;
	P_IP s,c;

	fp=fopen("in.txt","r");

	//printf("input the number of insert points:");
	//scanf("%d",&n);

	//初始化三对角矩阵
    p=init_threediagMatrix(n);

	//读入插值条件
	s=(P_IP)malloc((n+2)*sizeof(IP));//第一型插值，共n+2个条件
	c=(P_IP)malloc((n+2)*sizeof(IP));
	getIP(s,n);
	copy(c,s,n);
	kernel_1(p,s,n);
	printf("******************************************************\n");
	printf("Written by Chenjianglong....\n");
	printf("pattern 1/(25*x^2+1)\n");
	printf("default 11 points....\n");
	printf("read date from in.txt...\n");
	printf("******************************************************\n");
	printf(" X       precision value       s(x)             p(x)\n");
	for(i=1;i<=20;i++)
	{
		fscanf(fp,"%f",&x);
	    printf("%f     %.5f          %.5f          %.5f\n",x,(float)1/(25*x*x+1),kernel_2(x,s,n),lagrange(c,n,x));
	}

	free(s);
	free(c);
	free_mem(p,n);
	system("PAUSE");
}

void getIP(P_IP s,int n)
{
	int i;
	float x,h;
	//读入插值点
	//for(i=0;i<n;i++)
	//{
    //printf("intput the %dth point :",i+1);
	//	scanf("%f,%f",&(s+i)->x,&(s+i)->y);
	//}
	//读入第一个和最后一个点处的导数值
	//printf("intput the ds at (%f,%f) :",s[0].x,s[0].y);
	//scanf("%f",&s[i].y);
	//printf("intput the ds at (%f,%f) :",s[n-1].x,s[n-1].y);
	//scanf("%f",&s[i+1].y);

	//  生成插值节点
	
	for(i=0;i<n;i++)
	{
		x=-1+(float)i/5;
		s[i].x=x;
		s[i].y=1/(1+25*x*x);
	}
	h=s[1].x-s[0].x;
	s[n].y=-(float)50/676;
	s[n+1].y=-s[n].y;
}
float **init_threediagMatrix(int n)
{
	int i;
	float **p;
	p=(float **)malloc(n*sizeof(float *));
	for(i=0;i<n;i++)
		*(p+i)=malloc(sizeof(float)*n);
	p[0][0]=p[n-1][n-1]=2;
	for(i=1;i<n;i++)
		p[i][i-1]=p[i-1][i]=1;
	for(i=1;i<=n-2;i++)
		p[i][i]=4;
	//for(i=0;i<=n-3;i++)
		//for(j=i+2;j<=n-1;j++)
		//	p[i][j]=p[j][i]=0;
	return p;
}

void kernel_1(float **a,P_IP s,int n)//追赶法
{
	int i;
	float h;//节点距离
	float temp;

	//计算h
	h=s[1].x-s[0].x;
	//L U分解
	for(i=1;i<=n-1;i++)
	{
		a[i][i-1]=a[i][i-1]/a[i-1][i-1];
		a[i][i]=a[i][i]-a[i][i-1]*a[i-1][i];
	}

	//矫正y[i]
	s[0].y=3*s[0].y+h*s[n].y;
	s[n-1].y=3*s[n-1].y-h*s[n+1].y;
	for(i=1;i<=n-2;i++)
		s[i].y*=6;
	//矫正 x[i]
	
	for(i=n;i>=1;i--)
		s[i].x=s[i-1].x;
	s[0].x=s[1].x-h;
	s[n+1].x=s[n].x+h;
	//find x y
	for(i=1;i<=n-1;i++)
		s[i].y=s[i].y-a[i][i-1]*s[i-1].y;//find y
	s[n-1].y=s[n-1].y/a[n-1][n-1];
	for(i=n-2;i>=0;i--)
		s[i].y=(s[i].y-a[n-2][n-1]*s[i+1].y)/a[i][i];//find x
	temp=s[1].y-2*h*s[n].y;//计算c -1
	for(i=n;i>=1;i--)// 位置变换
		s[i].y=s[i-1].y;
	s[0].y=temp;
	temp=2*h*s[n+1].y+s[n-1].y;//计算c n+1
	s[n+1].y=temp;
}
float kernel_2(float x,P_IP s,int n)
{
	int i;
	float h=s[1].x-s[0].x;
	float sum=0;
	for(i=0;i<=n+1;i++)
		sum+=s[i].y*comput_M4((x-s[i].x)/h);

	return sum;
}
float comput_M4(float x)
{
	float y=fabs(x);
	if(y>=2)
		return 0;
	else if(y<=1)
		return 0.5*y*y*y-y*y+(float)2/3;
	else
		return -y*y*y/6+y*y-2*y+(float)4/3;
}
void free_mem(float **p,int n)
{
	int i;
	for(i=0;i<n;i++)
		free(*(p+i));
	free(p);
}
void copy(P_IP c,P_IP s,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		c[i].x=s[i].x;
		c[i].y=s[i].y;
	}
}
float lagrange(P_IP s,int n,float x)
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


