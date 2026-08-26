/*TOMAS CORCHO VENTURA*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void triangSup(double **matU, double *t, double *sol, int n);
double **prodMat(double **a, int filA, int colA, double **b, int colB);

int main(void){
	double **a,**b,**c,*x,*y,tiempototal;
	int i,j,n;
	clock_t inicio,fin;
	
	printf("n?\t");
	scanf(" %d",&n);

	/*En aquest main tambe farem una prova de la funcio de producte de matrius*/
	a=(double**)malloc(n*sizeof(double*));
	if(a==NULL){
		printf("error");
		exit(1);
	}
	b=(double**)malloc(n*sizeof(double*));
	if(b==NULL){
		printf("error");
		exit(1);
	}
	for(i=0;i<n;i++){
		a[i]=(double*)malloc(n*sizeof(double));
		b[i]=(double*)malloc(n*sizeof(double));
		if(a[i]==NULL || b[i]==NULL){
			printf("error");
			exit(1);
		}
	}
	y=(double*)malloc(n*sizeof(double));
	if(y==NULL){
		printf("error");
		exit(1);
	}
	x=(double*)malloc(n*sizeof(double));
	if(x==NULL){
		printf("error");
		exit(1);
	}
	/*Omplenem a*/
	for(i=0;i<n;i++){
		for(j=i;j<n;j++){
			if((i+j)%2==1){
				a[i][j]=1.;
			}else{
				a[i][j]=-1.;
			}
		}
	}
	for(i=0;i<n;i++){
		a[i][i]=1.;
	}
	for(i=1;i<n;i++){
		for(j=0;j<i;j++){
			a[i][j]=0.;
		}
	}

	/*Omplenem y*/
	for(i=0;i<n;i++){
		y[i]=1.;
	}

	/*Impresio de a si volem verificar*/
	/*	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%.1e  ",a[i][j]);
		}
		printf("\n");
	}
	*/
	inicio=clock();
	triangSup(a,y,x,n);
	fin=clock();
	/*Impresio resultat (no cal imprimir si n es molt gran)*/
	if(n<20){
		for(i=0;i<n;i++){
			printf("x[%d] %.10e\t\n",i,x[i]);
		}
	}
	tiempototal=(double)(fin-inicio)/ CLOCKS_PER_SEC;
	printf("Temps: %.10e\n",tiempototal);

	/*PRODUCTE DE MATRIUS AQUI (com es tracta d'un exemple nomes ho farem si n petit)*/
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			a[i][j]=0.;
			b[i][j]=0.;
		}
	}
	if(n>8){
		for(i=0;i<n;i++){
			free(a[i]);
			free(b[i]);
		}
		free(a);
		free(y);
		free(b);
		free(x);
		return 0;
	}else{
	/*triang inf*/
		for(i=0;i<n;i++){
			for(j=0;j<=i;j++){
				a[i][j]=(double)(i+1)+j;
				b[i][j]=(double)(-2*i)+j*j+5.;
			}
		}
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				printf("%.10e\t",a[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				printf("%.10e\t",b[i][j]);
			}
			printf("\n");
		}

		c=prodMat(a,n,n,b,n);
		printf("\n");
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				printf("%.10e\t",c[i][j]);
			}
			printf("\n");
		}
	}
	/*alliberar memoria*/
	for(i=0;i<n;i++){
		free(a[i]);
		free(b[i]);
		free(c[i]);
	}
	free(a);
	free(y);
	free(b);
	free(c);
	free(x);
	return 0;
}
