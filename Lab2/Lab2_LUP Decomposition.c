//LUP Decomposition

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

int lupDecomposition(double **A, int *P, int n) {
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

double** allocateMatrix(int n) {
    int i;
    double **mat=(double**)malloc(n*sizeof(double*));
    for(i=0;i<n;i++) mat[i]=(double*)calloc(n,sizeof(double));
    return mat;
}

void freeMatrix(double **mat,int n) {
    int i;
    for(i=0;i<n;i++) free(mat[i]);
    free(mat);
}

void printMatrix(double **M,int n) {
    int i,j;
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) printf("%8.4f ",M[i][j]);
        printf("\n");
    }
}

int main() {
    int n,i,j;
    double **A,**L,**U;
    int *P;
    printf("Enter size of square matrix (n): ");
    scanf("%d",&n);
    A=allocateMatrix(n);
    printf("Enter elements of matrix A (%d x %d), row by row:\n",n,n);
    for(i=0;i<n;i++) for(j=0;j<n;j++) scanf("%lf",&A[i][j]);
    P=(int*)malloc(n*sizeof(int));
    if(!lupDecomposition(A,P,n)) {
        freeMatrix(A,n);
        free(P);
        return 0;
    }
    L=allocateMatrix(n);
    U=allocateMatrix(n);
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            if(i>j) L[i][j]=A[i][j];
            else if(i==j) L[i][j]=1.0;
            else L[i][j]=0.0;
            if(i<=j) U[i][j]=A[i][j];
            else U[i][j]=0.0;
        }
    }
    printf("\nPermutation vector P:\n");
    for(i=0;i<n;i++) printf("%d ",P[i]);
    printf("\n\nLower triangular matrix L:\n");
    printMatrix(L,n);
    printf("\nUpper triangular matrix U:\n");
    printMatrix(U,n);
    freeMatrix(A,n);
    freeMatrix(L,n);
    freeMatrix(U,n);
    free(P);
    return 0;
}

