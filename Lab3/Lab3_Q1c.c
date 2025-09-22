//Q1-c Quick Sort using median(middle) as pivot

#include <stdio.h>

void swap(int *a,int *b){
    int t=*a;
    *a=*b;
    *b=t;
}

int partition(int arr[],int low,int high,int printPivot){
    int mid=(low+high)/2;
    int pivot=arr[mid];
    if(printPivot){
        printf("Initial pivot chosen: %d\n",pivot);
    }
    swap(&arr[mid],&arr[high]);
    int i=low-1;
    int j;
    for(j=low;j<=high-1;j++){
        if(arr[j]<=pivot){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[high]);
    return i+1;
}

void quickSort(int arr[],int low,int high,int printPivot){
    if(low<high){
        int pi=partition(arr,low,high,printPivot);
        quickSort(arr,low,pi-1,0);
        quickSort(arr,pi+1,high,0);
    }
}

int main(){
    int n,i;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    int arr[n];
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    quickSort(arr,0,n-1,1);
    printf("Sorted array: ");
    for(i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}

