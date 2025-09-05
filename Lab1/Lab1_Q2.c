#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Binary Search Function
int binarySearch(int arr[], int l, int r, int key) {
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == key)
            return mid;
        if (arr[mid] < key)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

// Ternary Search Function
int ternarySearch(int arr[], int l, int r, int key) {
    while (l <= r) {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;

        if (arr[mid1] == key) return mid1;
        if (arr[mid2] == key) return mid2;

        if (key < arr[mid1])
            r = mid1 - 1;
        else if (key > arr[mid2])
            l = mid2 + 1;
        else {
            l = mid1 + 1;
            r = mid2 - 1;
        }
    }
    return -1;
}

int main() {
    int n, key;
    printf("Enter the size of array (n): ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    int i;
    for ( i = 0; i < n; i++) {
        arr[i] = i * 1.5;  
    }

    printf("Enter the key element to search: ");
    scanf("%d", &key);

    clock_t start, end;
    double time_binary, time_ternary;
    int index_binary = -1, index_ternary = -1;

    int iterations = 1000000; 
    start = clock();
    for (i = 0; i < iterations; i++) {
        index_binary = binarySearch(arr, 0, n - 1, key);
    }
    end = clock();
    time_binary = ((double)(end - start)) / CLOCKS_PER_SEC;  

    start = clock();
    for (i = 0; i < iterations; i++) {
        index_ternary = ternarySearch(arr, 0, n - 1, key);
    }
    end = clock();
    time_ternary = ((double)(end - start)) / CLOCKS_PER_SEC;  // total time

    // Results
    if (index_binary != -1)
        printf("\nBinary Search: Key found at index %d", index_binary);
    else
        printf("\nBinary Search: Key not found");

    if (index_ternary != -1)
        printf("\nTernary Search: Key found at index %d", index_ternary);
    else
        printf("\nTernary Search: Key not found");

    printf("\nTotal time taken by Binary Search (%d searches): %.6f seconds", iterations, time_binary);
    printf("\nTotal time taken by Ternary Search (%d searches): %.6f seconds", iterations, time_ternary);

    if (time_binary < time_ternary)
        printf("\n\nBinary Search is faster.\n");
    else if (time_binary > time_ternary)
        printf("\n\nTernary Search is faster.\n");
    else
        printf("\n\nBoth took equal time.\n");

    free(arr);
    return 0;
}

