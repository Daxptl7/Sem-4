#include<stdio.h>
#include<time.h>

void swap(int* num1, int* num2)
{
    int temp = *num1;   
    *num1 = *num2;      
    *num2 = temp;
}


void quick_sort(int arr[] , int start , int end)
{

    if (start >= end)
    return;

    int i = start -1;
    int j = start;
    int pivot = end;

    while(j<pivot)
    {
        if(arr[j]<arr[pivot])
        {
            i++;
            swap(&arr[i],&arr[j]);
        }
        j++;
    }
    i++;
    swap(&arr[i],&arr[pivot]);
    quick_sort(arr,start,i-1);
    quick_sort(arr,i+1,end);
}

int main()
{

    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int arr[size];

    for (int i = 0; i < size; i++)
    {
        printf("Enter the number: ");
        scanf("%d", &arr[i]);
    }

    quick_sort(arr, 0, size - 1);

    printf("\nSorted array: ");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);


    printf("\n");
    printf("This will also sort he array in the NlogN TC.\n");

    printf("Work flow : pahle i and j to start and start-1 le lenge baad me hum loop chalyge usse apne sahi jagah parr le jan e ke liye and also afer that we make conclusion of the recustion to solve the remainig  ones so this is the other way to do quick sort");

    return 0;
}