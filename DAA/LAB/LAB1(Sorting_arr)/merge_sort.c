#include <stdio.h>
#include <time.h>

void merge1(int arr[], int start, int mid, int end) {
    int len1 = mid - start + 1;
    int len2 = end - mid;
    
    int left[len1], right[len2];
    
    
    for (int i = 0; i < len1; i++)
    left[i] = arr[start + i];
    
    
    for (int j = 0; j < len2; j++)
    right[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = start;
    
    // dono array ko merge karr denge
    while (i < len1 && j < len2) {
        if (left[i] < right[j])
        arr[k++] = left[i++];
        else
        arr[k++] = right[j++];
    }
    
    //copy karr denge
    while (i < len1)
    arr[k++] = left[i++];
    
    while (j < len2)
    arr[k++] = right[j++];
}

void merge_sort(int arr[], int start, int end) {
    if (start >= end)
        return;

    int mid = start + (end - start) / 2;

    //do array bana diye equl devide karke
    merge_sort(arr, start, mid);
    merge_sort(arr, mid + 1, end);

    //dono ko merge kar diya;
    merge1(arr, start, mid, end);
}

int main() {
    int size;
    
    printf("Enter the size: ");
    scanf("%d", &size);

    int arr[size];

    for (int i = 0; i < size; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    merge_sort(arr, 0, size - 1);

    printf("\nSorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    } 

    printf("\n");

    printf("This algo will done the sorting the nlogn Time complaxity");

    return 0;
}
