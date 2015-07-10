//Product Chebyshev ploy and slove it!
//Written by Chenjianglong 2009.5.18
//run in vc++ 6.0
//ChenJianglong All the rights reserve!
//the author is unaccountable to the similar progarms!

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct boundray
{
    float min;
	float max;
}boun,*P_boun;

void FindNextPloy(int *p,int *q,int *t);
void BinFind(int *q,int n,P_boun bdr);
float PolyVal(float x,int *q);
void main()
{
	int i,j;
	int n;
	int *p,*q,*t;
	P_boun bdr;

	printf("******************************************************\n");
	printf("Product Chebyshev ploy(rank=n) and slove it!\n");
	printf("Written by ChenJianglong 2009.5.18\n");
	printf("******************************************************\n");
	printf("input the rank of model Chebyshev (n>=2):");
	scanf("%d",&n);

	//根据三项递推公式，最少存储两个多项式
	p=(int *)malloc((n+2)*sizeof(int));
	q=(int *)malloc((n+2)*sizeof(int));
	t=(int *)malloc((n+2)*sizeof(int));
	bdr=(P_boun)malloc(sizeof(boun)*(n+1));
	//第一项存储多项式的项数，初始化前两个多项式T0,T1
	p[0]=0;
	p[1]=1;
	q[0]=1;
	q[1]=1;
	q[2]=0;

	printf("T0 :1\nNo solution!\n\n");
	printf("T1 :1 0\nsolution:0\n\n");
	bdr[0].min=-1;
	bdr[0].max=0;
	bdr[1].min=0;
	bdr[1].max=1;
	for(i=2;i<=n;i++)
	{
		FindNextPloy(p,q,t);
		printf("T%d :",i);
		for(j=1;j<=q[0]+1;j++)
			printf("%d ",q[j]);
		printf("\n");
		BinFind(q,i,bdr);
		printf("solution:");
		for(j=0;j<i;j++)
			printf("%f ",bdr[j].max);
		printf("\n\n");
	}
	system("PAUSE");
}
void FindNextPloy(int *p,int *q,int *t)
{
	int i;

	//q[i]临时存储在t[i]
	t[0]=q[0];
	for(i=1;i<=q[0]+1;i++)
		t[i]=q[i];

	//q[i]*2
	q[0]++;
	q[q[0]+1]=0;
	for(i=1;i<=q[0]+1;i++)
		q[i]=q[i]*2;

	//生成新的q[i]
	for(i=q[0]+1;i>2;i--)
		q[i]=q[i]-p[i-2];

	for(i=0;i<=t[0]+1;i++)
		p[i]=t[i];
}
void BinFind(int *q,int n,P_boun bdr)
{
	int i;
	float x,y;
	bdr[n].max=bdr[n-1].max;
	for(i=0;i<n;i++)
	{
		x=(bdr[i].min+bdr[i].max)/2;
		while(fabs(y=PolyVal(x,q))>=0.00001)
		{
			if(PolyVal(bdr[i].min,q)*y>0)
				bdr[i].min=x;
			else
				bdr[i].max=x;
			if(fabs(bdr[i].max-bdr[i].min)<0.000001)//how to deal with it??
				break;
			x=(bdr[i].min+bdr[i].max)/2;
		}
		if(i!=0)
		    bdr[i].min=bdr[i-1].max;
		bdr[i].max=x;
	}
	bdr[0].min=-1;
	bdr[i].min=bdr[i-1].max;
}
float PolyVal(float x,int *q)
{
	int i,j;
	float sum=0,temp;
	for(i=1;i<=q[0];i++)
	{
		temp=1;
		for(j=1;j<=q[0]+1-i;j++)
			temp=temp*x;
		sum=sum+temp*q[i];
	}
	return sum+q[i];
}