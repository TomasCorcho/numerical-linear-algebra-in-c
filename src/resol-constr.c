/*TOMAS CORCHO VENTURA*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void triangSup(double **matU, double *t, double *sol, int n);
int pivot(double **matA, int pas, int n);
int gauss(double **a, double *b, double tol, int n);

int main(void){
	int i,j,n;
	double tol,**a,*b,*x;

	printf("n?\t");
	scanf(" %d", &n);

	printf("tol?\t");
	scanf(" %lf",&tol);
	
	a=(double**)malloc(n*sizeof(double*));
	if(a==NULL){
		printf("error");
		exit(1);
	}
	for(i=0;i<n;i++){
		a[i]=(double*)malloc(n*sizeof(double));
		if(a[i]==NULL){
			printf("error");
			exit(1);
		}
	}
	b=(double*)malloc(n*sizeof(double));
	if(b==NULL){
		printf("error");
		exit(1);
	}
	x=(double*)malloc(n*sizeof(double));
	if(x==NULL){
		printf("error");
		exit(1);
	}

	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			a[i][j]=1./((i+1)+(j+1)-1.);
		}
		b[i]=(double)(i+1);
	}
	

	j=gauss(a,b,tol,n);

	if(j==1){
		triangSup(a,b,x,n);
		printf("Solucio:\n");
		for(i=0;i<n;i++){
			printf("x[%d] = %.10e\n",i,x[i]);
		}
	}else{
		printf("Es tracta d'un sistema numericament singular amb aquesta n i tol\n");
	}
	free(x);
	free(b);
	for(i=0;i<n;i++){
		free(a[i]);
	}
	free(a);
	return 0;
}
