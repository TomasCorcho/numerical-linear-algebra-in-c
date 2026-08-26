/*TOMAS CORCHO VENTURA*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void triangSup(double **matU, double *t, double *sol, int n);
int gauss(double **a, double *b, double tol, int n);
double **prodMat(double **a, int filA, int colA, double **b, int colB);

int main(void){
	int i,j,n,m,ok;
	double tol,**a,**at,**b,**c,*d,**aux,*x; /*	b=at*a	*/
	
	tol=1e-10;

	printf("n? m?\t");
	scanf(" %d %d", &n, &m);

	a=(double**)malloc(n*sizeof(double*));
	if(a==NULL){
		printf("error");
		exit(1);
	}
	at=(double**)malloc(m*sizeof(double*));
	if(at==NULL){
		printf("error");
		exit(1);
	}
	c=(double**)malloc(n*sizeof(double*));
	if(c==NULL){
		printf("error");
		exit(1);
	}
	x=(double*)malloc(m*sizeof(double));
	if(x==NULL){
		printf("error");
		exit(1);
	}
	d=(double*)malloc(m*sizeof(double));
	if(d==NULL){
		printf("error");
		exit(1);
	}
	for(i=0;i<n;i++){
		a[i]=(double*)malloc(m*sizeof(double));
		if(a[i]==NULL){
			printf("error");
			exit(1);
		}
	}
	for(i=0;i<n;i++){
		c[i]=(double*)malloc(sizeof(double));
		if(c[i]==NULL){
			printf("error");
			exit(1);
		}
	}
	for(i=0;i<m;i++){
		at[i]=(double*)malloc(n*sizeof(double));
		if(at[i]==NULL){
			printf("error");
			exit(1);
		}
	}

	/*Construim a i c*/
	printf("Ara cal introduir la matriu ampliada a ma:\n");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			scanf(" %lf",&a[i][j]);
		}
		scanf(" %lf",&c[i][0]);
	}

	/*Construim at*/
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			at[j][i]=a[i][j];
		}
	}

	b=prodMat(at, m, n, a, m);
	aux=prodMat(at, m, n, c, 1);
	
	for(i=0;i<m;i++){
		d[i]=aux[i][0];
	}

	ok=gauss(b,d,tol,m);
	if(ok==1){
		triangSup(b,d,x,m);
		printf("Solucio:\n");
		for(i=0;i<m;i++){
			printf("%.10e\t",x[i]);
		}
	}else{
		printf("La matriu es numericament singular");
	}
	printf("\n");

	for(i=0;i<n;i++){
		free(a[i]);
		free(c[i]);
	}
	for(i=0;i<m;i++){
		free(b[i]);
		free(at[i]);
		free(aux[i]);
	}
	free(aux);
	free(d);
	free(c);
	free(x);
	free(a);
	free(at);
	free(b);
	return 0;
}
