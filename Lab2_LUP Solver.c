//LUP Solver

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

double** allocateMatrix(int n) {
    int i;
    double **mat = (double**)malloc(n*sizeof(double*));
    for(i=0;i<n;i++) mat[i]=(double*)calloc(n,sizeof(double));
    return mat;
}

void freeMatrix(double **mat,int n) {
    int i;
    for(i=0;i<n;i++) free(mat[i]);
    free(mat);
}

int lupDecomposition(double **A,int *P,int n) {
    int i,j,k,temp,k_prime;
    double p;
    double *row_temp;
    for(i=0;i<n;i++) P[i]=i;
    for(k=0;k<n;k++) {
        p=0.0;
        k_prime=-1;
        for(i=k;i<n;i++) {
            if(fabs(A[i][k])>p) {
                p=fabs(A[i][k]);
                k_prime=i;
            }
        }
        if(p<EPSILON) return 0;
        temp=P[k];
        P[k]=P[k_prime];
        P[k_prime]=temp;
        row_temp=A[k];
        A[k]=A[k_prime];
        A[k_prime]=row_temp;
        for(i=k+1;i<n;i++) {
            A[i][k]/=A[k][k];
            for(j=k+1;j<n;j++) A[i][j]-=A[i][k]*A[k][j];
        }
    }
    return 1;
}

void forwardSubstitution(double **L,double *b,double *y,int *P,int n) {
    int i,j;
    for(i=0;i<n;i++) {
        y[i]=b[P[i]];
        for(j=0;j<i;j++) y[i]-=L[i][j]*y[j];
    }
}

void backwardSubstitution(double **U,double *y,double *x,int n) {
    int i,j;
    for(i=n-1;i>=0;i--) {
        x[i]=y[i];
        for(j=i+1;j<n;j++) x[i]-=U[i][j]*x[j];
        x[i]/=U[i][i];
    }
}

int lupSolve(double **A,int *P,double *b,double *x,int n) {
    int i,j;
    double **L=allocateMatrix(n);
    double **U=allocateMatrix(n);
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            if(i>j) L[i][j]=A[i][j];
            else if(i==j) L[i][j]=1.0;
            else L[i][j]=0.0;
            if(i<=j) U[i][j]=A[i][j];
            else U[i][j]=0.0;
        }
    }
    double *y=(double*)malloc(n*sizeof(double));
    forwardSubstitution(L,b,y,P,n);
    backwardSubstitution(U,y,x,n);
    freeMatrix(L,n);
    freeMatrix(U,n);
    free(y);
    return 1;
}

int main() {
    int n,i,j;
    double **A,*b,*x;
    int *P;
    printf("Enter size of matrix (n): ");
    scanf("%d",&n);
    A=allocateMatrix(n);
    b=(double*)malloc(n*sizeof(double));
    x=(double*)malloc(n*sizeof(double));
    P=(int*)malloc(n*sizeof(int));
    printf("Enter matrix A (%d x %d):\n",n,n);
    for(i=0;i<n;i++) for(j=0;j<n;j++) scanf("%lf",&A[i][j]);
    printf("Enter vector b (%d elements):\n",n);
    for(i=0;i<n;i++) scanf("%lf",&b[i]);
    if(!lupDecomposition(A,P,n)) {
        freeMatrix(A,n);
        free(b);
        free(x);
        free(P);
        printf("Matrix is singular or near-singular.\n");
        return 0;
    }
    lupSolve(A,P,b,x,n);
    printf("\nSolution vector x:\n");
    for(i=0;i<n;i++) printf("x[%d] = %.6f\n",i,x[i]);
    freeMatrix(A,n);
    free(b);
    free(x);
    free(P);
    return 0;
}

