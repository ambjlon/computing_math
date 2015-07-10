#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct infor_matrix
{
	float **p;
	int ln;
	int col;
}Matrix,*PMatrix;

float find_abs(PMatrix a,int a_col);
void find_q(PMatrix a,PMatrix q,int q_col,float r);
float a_and_q(PMatrix a,PMatrix q,int q_col,int a_col);
void correct_a(PMatrix a,PMatrix q,PMatrix r,int start);
void turn_matrix(PMatrix q);
float *multiply_matrix(PMatrix q,float *b,int c_size);
void main(void)
{
	int i,j,k;
	PMatrix a,q,r;
	float *b;
	float *c;
	int c_size;

	a=(PMatrix)malloc(sizeof(Matrix));
	printf("input the infor about matrix a:\n");
	printf("ln col:");
	scanf("%d%d",&a->ln,&a->col);
	a->p=(float **)malloc(a->ln*sizeof(float *));
	a->p[0]=(float *)malloc(a->ln*a->col*sizeof(float));
	for(i=1;i<=a->ln-1;i++)
		a->p[i]=a->p[i-1]+a->col;
	printf("input Matrix a:\n");
	for(i=0;i<=a->ln-1;i++)
		for(j=0;j<=a->col-1;j++)
			scanf("%f",a->p[i]+j);
	printf("input b:\n");
	b=(float *)malloc(a->ln*sizeof(float));
	for(i=0;i<=a->ln-1;i++)
	scanf("%f",b+i);

	q=(PMatrix)malloc(sizeof(Matrix));
	q->ln=a->ln;
	q->col=a->col;
	q->p=(float **)malloc(q->ln*sizeof(float *));
	q->p[0]=(float *)malloc(q->ln*q->col*sizeof(float));
	for(i=1;i<=q->ln-1;i++)
		q->p[i]=q->p[i-1]+q->col;

    r=(PMatrix)malloc(sizeof(Matrix));
	r->ln=a->col;
	r->col=a->col;
	r->p=(float **)malloc(r->ln*sizeof(float *));
	r->p[0]=(float *)malloc(r->ln*r->col*sizeof(float));
	for(i=1;i<=r->ln-1;i++)
		r->p[i]=r->p[i-1]+r->col;



	for(i=0;i<=a->ln-1;i++)
	{
		r->p[i][i]=find_abs(a,i);
        find_q(a,q,i,r->p[i][i]);
        for(j=i+1;j<=a->ln-1;j++)
			r->p[i][j]=a_and_q(a,q,i,j);
			correct_a(a,q,r,i+1);
	}
    
    
	c_size=q->col;
	turn_matrix(q);
	c=mutiply(q,b,c_size);


}

float find_abs(PMatrix a,int a_col)
{
	int i;
	float result=0;
	for(i=0;i<=a->ln-1;i++)
    result+=a->p[i][a_col]*a->p[i][a_col];
	return sqrt(result);
}
void find_q(PMatrix a,PMatrix q,int q_col,float r)
{
	int i;
	for(i=0;i<=a->ln-1;i++)
		q->p[i][q_col]=a->p[i][q_col]/r;
}
float a_and_q(PMatrix a,PMatrix q,int q_col,int a_col)
{
	int i;
	float result=0;
	for(i=0;i<=a->ln-1;i++)
		result+=q->p[i][q_col]*a->p[i][a_col];
	return result;
}
void correct_a(PMatrix a,PMatrix q,PMatrix r,int start)
{
	int i,j;
	for(i=start;i<=a->col-1;i++)
	for(j=0;j<=a->ln-1;j++)
		a->p[j][i]-=r->p[start-1][i]*q->p[start-1][j];
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

float *multiply_matrix(PMatrix q,float *b,int c_size)
{
  int i,j;
  float temp;
  float *c;
  c=(float *)malloc(c_size*sizeof(float));
  for(i=0;i<=c_size-1;i++)
  {
	  temp=0
      for(j=0;j<=q->col-1;j++)
		  temp+=q->p[i][j]*b[j];
	  c[i]=temp;
  }
  return c;
}