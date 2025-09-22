// Strassens 
#include <stdio.h>
#include <stdlib.h>

int** allocateMatrix(int n) {
    int i;
    int** mat = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++)
        mat[i] = (int*)calloc(n, sizeof(int));
    return mat;
}


void freeMatrix(int** mat, int n) {
    int i;
    for (i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

void copyBlock(int** src, int** dest, int r, int c, int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            dest[i][j] = src[i + r][j + c];
}


void pasteBlock(int** src, int** dest, int r, int c, int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            dest[i + r][j + c] = src[i][j];
}

void addMatrix(int** A, int** B, int** C, int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subMatrix(int** A, int** B, int** C, int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int** A11 = allocateMatrix(k); int** A12 = allocateMatrix(k);
    int** A21 = allocateMatrix(k); int** A22 = allocateMatrix(k);
    int** B11 = allocateMatrix(k); int** B12 = allocateMatrix(k);
    int** B21 = allocateMatrix(k); int** B22 = allocateMatrix(k);

    copyBlock(A, A11, 0,   0,   k);
    copyBlock(A, A12, 0,   k,   k);
    copyBlock(A, A21, k,   0,   k);
    copyBlock(A, A22, k,   k,   k);

    copyBlock(B, B11, 0,   0,   k);
    copyBlock(B, B12, 0,   k,   k);
    copyBlock(B, B21, k,   0,   k);
    copyBlock(B, B22, k,   k,   k);

    int** M1 = allocateMatrix(k); int** M2 = allocateMatrix(k); int** M3 = allocateMatrix(k);
    int** M4 = allocateMatrix(k); int** M5 = allocateMatrix(k); int** M6 = allocateMatrix(k);
    int** M7 = allocateMatrix(k);
    int** T1 = allocateMatrix(k); int** T2 = allocateMatrix(k);

    addMatrix(A11, A22, T1, k);
    addMatrix(B11, B22, T2, k);
    strassen(T1, T2, M1, k);

    addMatrix(A21, A22, T1, k);
    strassen(T1, B11, M2, k);

    subMatrix(B12, B22, T1, k);
    strassen(A11, T1, M3, k);

    subMatrix(B21, B11, T1, k);
    strassen(A22, T1, M4, k);

    addMatrix(A11, A12, T1, k);
    strassen(T1, B22, M5, k);

    subMatrix(A21, A11, T1, k);
    addMatrix(B11, B12, T2, k);
    strassen(T1, T2, M6, k);

    subMatrix(A12, A22, T1, k);
    addMatrix(B21, B22, T2, k);
    strassen(T1, T2, M7, k);

    int** C11 = allocateMatrix(k); int** C12 = allocateMatrix(k);
    int** C21 = allocateMatrix(k); int** C22 = allocateMatrix(k);

    addMatrix(M1, M4, T1, k);
    subMatrix(T1, M5, T2, k);
    addMatrix(T2, M7, C11, k);

    addMatrix(M3, M5, C12, k);
    addMatrix(M2, M4, C21, k);

    subMatrix(M1, M2, T1, k);
    addMatrix(T1, M3, T2, k);
    addMatrix(T2, M6, C22, k);

    pasteBlock(C11, C, 0,   0,   k);
    pasteBlock(C12, C, 0,   k,   k);
    pasteBlock(C21, C, k,   0,   k);
    pasteBlock(C22, C, k,   k,   k);

    freeMatrix(A11,k); freeMatrix(A12,k); freeMatrix(A21,k); freeMatrix(A22,k);
    freeMatrix(B11,k); freeMatrix(B12,k); freeMatrix(B21,k); freeMatrix(B22,k);
    freeMatrix(M1,k);  freeMatrix(M2,k);  freeMatrix(M3,k);  freeMatrix(M4,k);
    freeMatrix(M5,k);  freeMatrix(M6,k);  freeMatrix(M7,k);
    freeMatrix(C11,k); freeMatrix(C12,k); freeMatrix(C21,k); freeMatrix(C22,k);
    freeMatrix(T1,k);  freeMatrix(T2,k);
}

int nextPowerOf2(int n) {
    int p = 1;
    while (p < n) p *= 2;
    return p;
}

int main() {
    int n, i, j;
    printf("Enter size of matrix (n x n): ");
    scanf("%d", &n);

    int** A = allocateMatrix(n);
    int** B = allocateMatrix(n);

    printf("\nEnter elements of matrix A (%d x %d):\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("A[%d][%d] = ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    printf("\nEnter elements of matrix B (%d x %d):\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("B[%d][%d] = ", i, j);
            scanf("%d", &B[i][j]);
        }
    }

    int m = nextPowerOf2(n);
    int** A_pad = allocateMatrix(m);
    int** B_pad = allocateMatrix(m);
    int** C_pad = allocateMatrix(m);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            A_pad[i][j] = A[i][j];
            B_pad[i][j] = B[i][j];
        }

    strassen(A_pad, B_pad, C_pad, m);

    printf("\nResultant matrix C (A x B):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%5d ", C_pad[i][j]);
        printf("\n");
    }

    freeMatrix(A, n); freeMatrix(B, n);
    freeMatrix(A_pad, m); freeMatrix(B_pad, m); freeMatrix(C_pad, m);

    return 0;
}

