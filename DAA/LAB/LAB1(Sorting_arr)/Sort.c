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
int  main()
{

    int size;

    printf("Enter the size of the array:");
    scanf("%d",&size);

    int arr[size];
    for(int i=0 ; i<size ;i++)
    {
        printf("Enter the number:");
        scanf("%d",&arr[i]);
    }

    for(int i=0 ; i<size ;i++)
    {
        printf("%d ",arr[i]);
    }

    printf("\n");
    
    bubble_sort(arr,size);
    
    printf("\n");
    
    selection_sort(arr,size);
    
    printf("\n");
    
    insertionSort(arr,size);
    
    printf("\n");
    printf("all this code is runnig in the N^2");

}