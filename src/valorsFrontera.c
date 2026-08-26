/*TOMAS CORCHO VENTURA*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double p1(double x);
double q1(double x);
double r1(double x);

double p2(double x);
double q2(double x);
double r2(double x);

double p(double x){
	return p2(x);
}
double q(double x){
	return q2(x);
}
double r(double x){
	return r2(x);
}

void triangSup(double **matU, double *t, double *sol, int n);
int gauss(double **a, double *b, double tol, int n);

int main(void){
	int i,j,m,fila,ok;
	double a,b,alpha,beta,h,pi,qi,ri,Ai,Bi,Ci,**mat,*y,*c,tol,xi;
	FILE *fp;

	tol=1e-10;

	printf("m, a, b?\t");
	scanf(" %d %lf %lf", &m, &a, &b);	
	
	printf("alpha, beta?\t");
	scanf(" %lf %lf", &alpha, &beta);
	
	fp=fopen("sortida.dat","w");
	if(fp==NULL){
		printf("error");
		exit(1);
	}
	mat=(double**)malloc((m-1)*sizeof(double*));
	if(mat==NULL){
		printf("error");
		exit(1);
	}
	for(i=0;i<(m-1);i++){
		mat[i]=(double*)malloc((m-1)*sizeof(double));
		if(mat[i]==NULL){
			printf("error");
			exit(1);
		}
	}
	y=(double*)malloc((m-1)*sizeof(double));
	if(y==NULL){
		printf("error");
		exit(1);
	}
	c=(double*)malloc((m-1)*sizeof(double));
	if(c==NULL){
		printf("error");
		exit(1);
	}

	h=(b-a)/m;
	/*Omplenem de zeros*/
	for(i=0;i<(m-1);i++){
		for(j=0;j<(m-1);j++){
			mat[i][j]=0.;
		}
	}
	/*Omplenem*/
	for(i=1;i<m;i++){
		fila=i-1;

		xi=a+i*h;
		pi=p(xi);
		qi=q(xi);
		ri=r(xi);
		Ai=(1./(h*h))+(pi/(2.*h));
		Bi=(-2./(h*h))-qi;	
		Ci=(1./(h*h))-(pi/(2.*h));
		
		mat[fila][fila]=Bi;
		
		c[fila]=ri;

		if(i>1){
			mat[fila][fila-1]=Ai;
		}else{
			c[fila]=c[fila]-Ai*alpha;
		}

		if(i<m-1){
			mat[fila][fila+1]=Ci;
		}else{
			c[fila]=c[fila]-Ci*beta;
		}
		
	}

	ok=gauss(mat,c,tol,m-1);

	if (ok==1){
		triangSup(mat,c,y,m-1);
		fprintf(fp,"%.10e\t%.10e\n",a,alpha);
		for(i=1;i<=m-1;i++){
			xi=a+i*h;
			fprintf(fp,"%.10e\t%.10e\n",xi, y[i-1]);
		}
		fprintf(fp,"%.10e\t%.10e\n",b,beta);
	}else{
		printf("La matriu es numericament singular");
	}
	

	fclose(fp);
	for(i=0;i<(m-1);i++){
		free(mat[i]);
	}
	free(mat);
	free(y);
	free(c);
	return 0;
}
