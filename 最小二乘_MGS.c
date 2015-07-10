/*求最小二乘解的MGS算法
  Written by ChenJianglong 2008.11.17*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef float Datetype;
typedef struct infor_matrix
{
	Datetype **p;
	int ln;
	int col;
}Matrix,*PMatrix;

Datetype find_abs(PMatrix a,int a_col);
void find_q(PMatrix a,PMatrix q,int q_col,Datetype r);
Datetype a_and_q(PMatrix a,PMatrix q,int q_col,int a_col);
void correct_a(PMatrix a,PMatrix q,PMatrix r,int start);
Datetype *find_c(PMatrix q,Datetype *b,int c_size);
void main(void)
{
	int i,j;
	PMatrix a,q,r;
	Datetype *b;
	Datetype *c;
	int c_size;
	Datetype temp;

	a=(PMatrix)malloc(sizeof(Matrix));
	printf("input the infor about matrix a:\n");
	printf("ln col:");
	scanf("%d%d",&a->ln,&a->col);
	a->p=(Datetype **)malloc(a->ln*sizeof(Datetype *));
	a->p[0]=(Datetype *)malloc(a->ln*a->col*sizeof(Datetype));
	for(i=1;i<=a->ln-1;i++)
		a->p[i]=a->p[i-1]+a->col;
	printf("input Matrix a:\n");
	for(i=0;i<=a->ln-1;i++)
		for(j=0;j<=a->col-1;j++)
			scanf("%f",a->p[i]+j);
	printf("input b:\n");
	b=(Datetype *)malloc(a->ln*sizeof(Datetype));
	for(i=0;i<=a->ln-1;i++)
	scanf("%f",b+i);

	q=(PMatrix)malloc(sizeof(Matrix));
	q->ln=a->ln;
	q->col=a->col;
	q->p=(Datetype **)malloc(q->ln*sizeof(Datetype *));
	q->p[0]=(Datetype *)malloc(q->ln*q->col*sizeof(Datetype));
	for(i=1;i<=q->ln-1;i++)
		q->p[i]=q->p[i-1]+q->col;

    r=(PMatrix)malloc(sizeof(Matrix));
	r->ln=a->col;
	r->col=a->col;
	r->p=(Datetype **)malloc(r->ln*sizeof(Datetype *));
	r->p[0]=(Datetype *)malloc(r->ln*r->col*sizeof(Datetype));
	for(i=1;i<=r->ln-1;i++)
		r->p[i]=r->p[i-1]+r->col;



	for(i=0;i<=a->col-1;i++)
	{
		r->p[i][i]=find_abs(a,i);
        find_q(a,q,i,r->p[i][i]);
        for(j=i+1;j<=a->col-1;j++)
			r->p[i][j]=a_and_q(a,q,i,j);
			correct_a(a,q,r,i+1);
	}
    
    
	c_size=q->col;
	c=find_c(q,b,c_size);

    c[c_size-1]/=r->p[r->ln-1][r->ln-1];
	for(i=c_size-2;i>=0;i--)
	{
      temp=0;
	  for(j=i+1;j<=r->col-1;j++)
		  temp+=r->p[i][j]*c[j];
	  c[i]=(c[i]-temp)/r->p[i][i];
	}

	printf("Result: \n");
	for(i=0;i<=c_size-1;i++)
		printf("%f\n",c[i]);
}

Datetype find_abs(PMatrix a,int a_col)
{
	int i;
	Datetype result=0;
	for(i=0;i<=a->ln-1;i++)
    result+=a->p[i][a_col]*a->p[i][a_col];
	return sqrt(result);
}
void find_q(PMatrix a,PMatrix q,int q_col,Datetype r)
{
	int i;
	for(i=0;i<=a->ln-1;i++)
		q->p[i][q_col]=a->p[i][q_col]/r;
}
Datetype a_and_q(PMatrix a,PMatrix q,int q_col,int a_col)
{
	int i;
	Datetype result=0;
	for(i=0;i<=a->ln-1;i++)
		result+=q->p[i][q_col]*a->p[i][a_col];
	return result;
}
void correct_a(PMatrix a,PMatrix q,PMatrix r,int start)
{
	int i,j;
	for(i=start;i<=a->col-1;i++)
	for(j=0;j<=a->ln-1;j++)
		a->p[j][i]-=r->p[start-1][i]*q->p[j][start-1];
}
void turn_matrix(PMatrix q)
{
	int i,j;
	int temp;
	for(i=0;i<=q->ln-1;i++)
		for(j=0;j<=q->col-1;j++)
			q->p[j][i]=q->p[i][j];
    temp=q->ln;
	q->ln=q->col;
	q->col=temp;
}

Datetype *find_c(PMatrix q,Datetype *b,int c_size)
{
  int i,j;
  Datetype temp;
  Datetype *c;
  c=(Datetype *)malloc(c_size*sizeof(Datetype));
  for(i=0;i<=c_size-1;i++)
  {
	  temp=0;
      for(j=0;j<=q->ln-1;j++)
		  temp+=q->p[j][i]*b[j];
	  c[i]=temp;
  }
  return c;
}