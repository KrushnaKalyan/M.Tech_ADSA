#include <stdio.h>
#include <math.h>
#include <string.h>
#define SIZE 12
typedef struct 
{
    char name[30];
    double value;
} Function;

void bubbleSort(Function arr[], int n) 
{
    int i, j;
    for (i = 0; i < n - 1; i++) 
	{
        for (j = 0; j < n - i - 1; j++) 
		{
            if (arr[j].value > arr[j + 1].value) 
			{
                Function temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() 
{
    double n;
    int i;
    Function funcs[SIZE];

    printf("Enter the value of n: ");
    scanf("%lf", &n);

    strcpy(funcs[0].name, "1/n");
    funcs[0].value = 1.0 / n;

    strcpy(funcs[1].name, "log2(n)");
    funcs[1].value = log2(n);

    strcpy(funcs[2].name, "2^32 * n");
    funcs[2].value = pow(2, 32) * n;

    strcpy(funcs[3].name, "12*sqrt(n)");
    funcs[3].value = 12 * sqrt(n);

    strcpy(funcs[4].name, "50*n^0.5");
    funcs[4].value = 50 * pow(n, 0.5);

    strcpy(funcs[5].name, "n^0.51");
    funcs[5].value = pow(n, 0.51);

    strcpy(funcs[6].name, "n log2(n)");
    funcs[6].value = n * log2(n);

    strcpy(funcs[7].name, "100n^2 + 6n");
    funcs[7].value = 100 * pow(n, 2) + 6 * n;

    strcpy(funcs[8].name, "n^2 - 324");
    funcs[8].value = pow(n, 2) - 324;

    strcpy(funcs[9].name, "2n^3");
    funcs[9].value = 2 * pow(n, 3);

    strcpy(funcs[10].name, "n^(log2 n)");
    funcs[10].value = pow(n, log2(n));

    strcpy(funcs[11].name, "3^n");
    funcs[11].value = (n > 50) ? INFINITY : pow(3, n);

    bubbleSort(funcs, SIZE);

    printf("\nSorted values for n = %.0f:\n", n);
    for (i = 0; i < SIZE; i++) 
	{
        if (isinf(funcs[i].value))
            printf("%2d. %-15s -> INF\n", i + 1, funcs[i].name);
        else
            printf("%2d. %-15s -> %.10e\n", i + 1, funcs[i].name, funcs[i].value);
    }

    return 0;
}

