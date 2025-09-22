//Q1-b Quick Sort-Merge Sort-Heap sort
#include <stdio.h>
#include <stdlib.h>

void quickSort(int arr[], int low, int high) {
    int i, j, pivot, temp;
    if (low < high) {
        pivot = arr[low];
        i = low;
        j = high;
        while (i < j) {
            while (arr[i] <= pivot && i <= high - 1) i++;
            while (arr[j] > pivot) j--;
            if (i < j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        temp = arr[low];
        arr[low] = arr[j];
        arr[j] = temp;
        quickSort(arr, low, j - 1);
        quickSort(arr, j + 1, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    int i, j, k;
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    int m;
    if (l < r) {
        m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int temp;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    int i, temp;
    for (i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (i = n - 1; i >= 0; i--) {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

void copyArray(int src[], int dest[], int n) {
    int i;
    for (i = 0; i < n; i++) dest[i] = src[i];
}

int main() {
    int n, i;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n], arrQuick[n], arrMerge[n], arrHeap[n];
    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) scanf("%d", &arr[i]);
    copyArray(arr, arrQuick, n);
    copyArray(arr, arrMerge, n);
    copyArray(arr, arrHeap, n);
    quickSort(arrQuick, 0, n - 1);
    mergeSort(arrMerge, 0, n - 1);
    heapSort(arrHeap, n);
    printf("Quick Sort: ");
    printArray(arrQuick, n);
    printf("Merge Sort: ");
    printArray(arrMerge, n);
    printf("Heap Sort: ");
    printArray(arrHeap, n);
    return 0;
}

