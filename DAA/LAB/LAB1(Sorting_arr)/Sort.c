#include<stdio.h>
#include<time.h>

int counter=0;
int swaps=0;

void bubble_sort(int arr[] , int size)
{
    int start_time = clock();
    for(int i=0 ; i < size-1 ; i++)
    {
        for(int j=0 ; j<size-i-1 ;j++)
        {
            counter++;
            if(arr[j]>arr[j+1])
            {
                swaps++;
                int temp = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    int end_time=clock();
    printf("Bubble sorted array is :");
    for(int i=0 ; i<size ;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("The comparisions for the Bubble sort is :%d \n",counter);
    
    printf("The total swaps that are happens is : %d \n",swaps);
    
    printf("Time taken for the Code to exicute is : %ds \n",(end_time-start_time)*1000/60);
    
}

void selection_sort(int arr[] ,int size)
{
    for(int i=0 ; i<size-1;i++)
    {
        int minindex = i;
        for(int j=i+1 ; j<size ; j++)
        {
            if(arr[j]<arr[minindex])
            {
               minindex=j;
            }
        }

        int temp = arr[minindex];
                arr[minindex]=arr[i];
                arr[i]=temp;
    }

    printf("selection sorted array is :");
    for(int i=0 ; i<size ;i++)
    {
        printf("%d ",arr[i]);
    }
}

void insertionSort(int arr[],int size) {
    for (int i = 1; i < size; i++) {

        int key = arr[i];
        int j = i - 1;


        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }

    printf("Insertion sorted array is :");
    for(int i=0 ; i<size ;i++)
    {
        printf("%d ",arr[i]);
    }
}

void swap(int* num1, int* num2)
{
    int temp = *num1;   
    *num1 = *num2;      
    *num2 = temp;
}

void quick_sort(int arr[], int start, int end)
{
    if (start >= end)
        return;

    int i = start - 1;
    int j = start;
    int pivot = end;

    while (j < pivot)
    {
        if (arr[j] < arr[pivot])
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
        j++;
    }

    i++;
    swap(&arr[i], &arr[pivot]);

    quick_sort(arr, start, i - 1);
    quick_sort(arr, i + 1, end);
}

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

int  main()
{

    int size;

    printf("Enter the size of the array: ");
    scanf("%d",&size);

    int original_arr[size];
    for(int i=0 ; i<size ;i++)
    {
        printf("Enter the number: ");
        scanf("%d",&original_arr[i]);
    }

    while (1) {
        int arr[size];
        for(int i=0 ; i<size ;i++)
        {
            arr[i] = original_arr[i];
        }

        printf("\nOriginal array: ");
        for(int i=0 ; i<size ;i++)
        {
            printf("%d ", arr[i]);
        }

        printf("\n\n");
        
        int choice;
        printf("Choose a sorting algorithm:\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Quick Sort\n");
        printf("5. Merge Sort\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        printf("\n");

        if (choice == 6) {
            printf("Exiting...\n");
            break;
        }

        switch (choice) {
            case 1:
                bubble_sort(arr, size);
                break;
            case 2:
                selection_sort(arr, size);
                break;
            case 3:
                insertionSort(arr, size);
                break;
            case 4:
                quick_sort(arr, 0, size - 1);
                printf("Quick sorted array is :");
                for(int i=0 ; i<size ;i++) {
                    printf("%d ",arr[i]);
                }
                break;
            case 5:
                merge_sort(arr, 0, size - 1);
                printf("Merge sorted array is :");
                for(int i=0 ; i<size ;i++) {
                    printf("%d ",arr[i]);
                }
                break;
            default:
                printf("Invalid choice!\n");
        }
        
        printf("\n");
        
        if (choice >= 1 && choice <= 3) {
            printf("All of these sorting algorithms run in O(N^2) time complexity.\n");
        } else if (choice == 4 || choice == 5) {
            printf("This algorithm sorts in O(N log N) time complexity.\n");
        }
        
        printf("--------------------------------------------------\n");
    }

    return 0;
}