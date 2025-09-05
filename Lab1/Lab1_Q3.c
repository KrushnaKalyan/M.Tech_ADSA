#include <stdio.h>

int compare_groups(const int coins[], int l1, int r1, int l2, int r2) 
{
    int i;
	long long sum1 = 0, sum2 = 0;  
    for (i = l1; i <= r1; ++i) sum1 += coins[i];
    for ( i = l2; i <= r2; ++i) sum2 += coins[i];

    if (sum1 < sum2) return -1;  
    if (sum1 > sum2) return 1;   
    return 0;                    
}
int findDefective(const int coins[], int l, int r) 
{
    int count = r - l + 1;
    if (count <= 0) return -1;
    if (count == 1) return l;
    int k = count / 2;                 
    int leftL = l;
    int leftR = l + k - 1;
    int rightL = r - k + 1;
    int rightR = r;

    int cmp = compare_groups(coins, leftL, leftR, rightL, rightR);
    if (cmp == -1) 
	{
        return findDefective(coins, leftL, leftR);
    } 
	else if (cmp == 1) 
	{
        return findDefective(coins, rightL, rightR);
    }
	else 
	{
        if (count % 2 == 1) return l + k;  
        return -1;                      
    }
}

int main() 
{
    int n,i;
    printf("Enter number of coins: ");
    if (scanf("%d", &n) != 1 || n <= 0) 
	{
        printf("Invalid n\n");
        return 0;
    }

    int coins[n];
    printf("Enter weights of coins: ");
    for ( i = 0; i < n; i++) scanf("%d", &coins[i]);

    int idx = findDefective(coins, 0, n - 1);
    if (idx == -1) 
	{
        printf("All coins are perfect (no lighter coin found)\n");
    } 
	else 
	{
        printf("Defective (lighter) coin at index %d with weight %d\n", idx, coins[idx]);
    }
    return 0;
}

