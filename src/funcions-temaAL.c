/*TOMAS CORCHO VENTURA*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void triangSup(double **matU, double *t, double *sol, int n){
	int i,j;
	double sum;
	for(i=n-1;i>=0;i--){
		sum=0.;
		for(j=i+1;j<n;j++){
			/*calcular suma*/
			sum=sum+matU[i][j]*sol[j];
			
		}
		sol[i]=(t[i]-sum)/matU[i][i];
	}
}

double **prodMat(double **a, int filA, int colA, double **b, int colB){
	int i,j,k;
	double **c;
	c=(double**)malloc(filA*sizeof(double*));
	if(c==NULL){
		printf("error");
		exit(1);
	}
	for(i=0;i<filA;i++){
		c[i]=(double*)malloc(colB*sizeof(double));
		if(c[i]==NULL){
			printf("error");
			exit(1);
		}
	}
	/*Inicialitzem*/
	for(i=0;i<filA;i++){
		for(j=0;j<colB;j++){
			c[i][j]=0.;
		}
	}
	for(i=0;i<filA;i++){
		for(j=0;j<colB;j++){
			for(k=0;k<colA;k++){
				c[i][j]=c[i][j]+a[i][k]*b[k][j];
			}
		}
	}
	return c;
}

int pivot(double **matA, int pas, int n){
	int i,imax;
	double max,aux;
	max=0.;
	imax=pas;
	for(i=pas;i<n;i++){
		aux=matA[i][pas];
		if(max<fabs(aux)){
			max=fabs(aux);
			imax=i;	
		}
	}
	return imax;
}

int gauss(double **a, double *b, double tol, int n){
	int i,j,k,piv;
	double m,*aux,baux;
	
	for(i=0;i<n;i++){
		piv=pivot(a,i,n);
		if(piv!=i){
			/*canvi de punters*/
			aux=a[piv];
			a[piv]=a[i];
			a[i]=aux;
			
			baux=b[piv];
			b[piv]=b[i];
			b[i]=baux;

		}
		if(fabs(a[i][i])<tol){
			return 0;
		}
		for(j=i+1;j<n;j++){
			m=a[j][i]/a[i][i];
			/*ara que ja tenim el multiplicador fem F_j=F_j-mF_i*/
			for(k=i;k<n;k++){
				a[j][k]=a[j][k]-m*a[i][k];
				if(fabs(a[j][k])<tol){
					a[j][k]=0.;
				}
			}
			b[j]=b[j]-m*b[i];
				
		}
	}
	return 1;
}
