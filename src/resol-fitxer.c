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
	FILE *fp,*gp;
	char ent[255],sort[255];

	printf("Fitxer entrada?\t");
	scanf(" %s", ent);

	printf("Fitxer sortida?\t");
	scanf(" %s",sort);

	fp=fopen(ent,"r");
	if(fp==NULL){
		printf("error");
		exit(1);
	}
	gp=fopen(sort,"w");
	if(gp==NULL){
		printf("error");
		exit(1);
	}

	fscanf(fp," %d", &n);
	
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
			fscanf(fp,"%lf", &a[i][j]);
		}
		fscanf(fp,"%lf",&b[i]);
	}
	fscanf(fp," %lf",&tol);

	j=gauss(a,b,tol,n);
	if(j==1){
		triangSup(a,b,x,n);
		for(i=0;i<n;i++){
			fprintf(gp,"%.10e\t",x[i]);
		}
	}else{
		printf("La matriu es numericament singular");
	}

	fclose(fp);
	fclose(gp);
	for(i=0;i<n;i++){
		free(a[i]);
	}
	free(a);
	free(b);
	free(x);
	return 0;
}
