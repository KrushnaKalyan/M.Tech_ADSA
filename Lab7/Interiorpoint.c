#include <stdio.h>
#include <math.h>

#define NMAX 20
#define MMAX 20

#define MU_FACTOR 0.5
#define ALPHA 0.01
#define INNER_ITERS 15000

void multiply(double r[], double A[][NMAX], double x[], int m, int n) {
    for (int i = 0; i < m; i++) {
        r[i] = 0.0;
        for (int j = 0; j < n; j++)
            r[i] += A[i][j] * x[j];
    }
}

double barrier_value(double x[], double c[], double mu, int n) {
    double s = 0.0;
    for (int i = 0; i < n; i++)
        s += c[i] * x[i] - mu * log(x[i]);
    return s;
}

void compute_grad(double g[], double x[], double c[], double mu, int n) {
    for (int i = 0; i < n; i++)
        g[i] = c[i] - mu / x[i];
}

int main() {
    int n, m;
    double A[MMAX][NMAX], b[MMAX], c[NMAX], x[NMAX];

    printf("Enter number of variables n: ");
    scanf("%d", &n);

    printf("Enter equality constraint m: ");
    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        printf("Provide Matrix A: ");
        for (int j = 0; j < n; j++)
        {
            
            scanf("%lf", &A[i][j]);
        }
    }
    printf("Vector b: ");
    for (int i = 0; i < m; i++)
    {
       
        scanf("%lf", &b[i]);
    }
    printf("Cost vector c: ");
    for (int i = 0; i < n; i++)
    {
        
        scanf("%lf", &c[i]);
    }

    for (int i = 0; i < n; i++)
        x[i] = 1.0;

    double mu = 1.0;

    for (int outer = 0; outer < 20; outer++) {

        for (int step = 0; step < INNER_ITERS; step++) {

            double g[NMAX];
            compute_grad(g, x, c, mu, n);

            for (int i = 0; i < n; i++) {
                x[i] -= ALPHA * g[i];
                if (x[i] <= 1e-9) x[i] = 1e-9;
            }

            double Ax[MMAX];
            multiply(Ax, A, x, m, n);

            for (int i = 0; i < m; i++) {
                double err = Ax[i] - b[i];
                for (int j = 0; j < n; j++)
                    x[j] -= 0.01 * err * A[i][j];
            }
        }

        printf("mu = %.6f  x = [", mu);
        for (int i = 0; i < n; i++)
            printf(" %.5f ", x[i]);
        printf("]  F = %.6f\n", barrier_value(x, c, mu, n));

        mu *= MU_FACTOR;
    }

    double obj = 0.0;
    for (int i = 0; i < n; i++)
        obj += c[i] * x[i];

    printf("\nSolution: [");
    for (int i = 0; i < n; i++)
        printf(" %.6f ", x[i]);
    printf("]\n");

    printf("Objective value: %.6f\n", obj);

    return 0;
}
