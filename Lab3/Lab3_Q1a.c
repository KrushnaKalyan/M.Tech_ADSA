//Q1-a Binary Search

#include <stdio.h>
int binarySearchIterative(int arr[], int n, int key) {
    int low = 0;
    int high = n - 1;
    int mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (arr[mid] == key)
            return mid;
        else if (key < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

int binarySearchRecursive(int arr[], int low, int high, int key) {
    int mid;
    if (low > high)
        return -1;
    mid = low + (high - low) / 2;
    if (arr[mid] == key)
        return mid;
    else if (key < arr[mid])
        return binarySearchRecursive(arr, low, mid - 1, key);
    else
        return binarySearchRecursive(arr, mid + 1, high, key);
}

// Sorting
void sortArray(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, i, key, result;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Sort the array first
    sortArray(arr, n);

    printf("Sorted array: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Enter key to search: ");
    scanf("%d", &key);

    result = binarySearchIterative(arr, n, key);
    if (result != -1)
        printf("Iterative: Key found at index %d\n", result);
    else
        printf("Iterative: Key not found\n");

    result = binarySearchRecursive(arr, 0, n - 1, key);
    if (result != -1)
        printf("Recursive: Key found at index %d\n", result);
    else
        printf("Recursive: Key not found\n");

    return 0;
}

