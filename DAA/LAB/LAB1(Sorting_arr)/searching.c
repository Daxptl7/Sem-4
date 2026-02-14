#include<stdio.h>
#include<time.h>
int counter = 0;
int linearsearch(int arr[] , int size , int target)
{
    int start_time = clock();
    for(int i=0 ; i<size ;i++)
    {
        counter++;
        if(arr[i]==target)
        {
            int end_time =clock();
            printf("The comparisions for the linear search is :%d \n",counter);
            printf("Time taken for the Code to exicute is : %ds \n",(end_time-start_time)/60);
            return i;
        }
    }
}

int binarysearch(int arr[] , int size , int target)
{
    int start = 0 ;
    int end = size-1;
    int mid  = start + (end - start)/2;

    while(start<end)
    {
        int start_time = clock();
        counter=0;
        counter++;
        if(arr[mid]==target)
        {
            int end_time =clock();
            return mid;
        }
        else if(arr[mid]<target)
        {
            start = mid + 1;
        }
        else
        {
            end = mid -1;
        }
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


int main()
{
    int size;
    printf("Enter the size of the Array:");
    scanf("%d",&size);

    int arr[size];
    for(int  i =0 ; i< size ; i++)
    {
        printf("Enter the element ar index %d :",i);
        scanf("%d",&arr[i]);
    }

    int target ;
    printf("Enter the target that you want to find in the arary:");
    scanf("%d",&target);
    
    printf("<--------------Linear search---------------->\n");
    printf("The element found at the index:%d",(linearsearch(arr,size,target)));
    printf("\n");
    printf("The Linearsearch found element is o(n) TC");
   
    printf("\n");
    printf("The array is :");
    for(int  i = 0 ; i<size ; i++)
    {
        printf("%d  ",arr[i]);
    }
    printf("\n");
    printf("<------------------Binary search-------------------->\n");

    printf("For binary search we Have first sort the elements\n");
    quick_sort(arr,0,size-1);
    printf("The sorted array is :");
    for(int  i = 0 ; i<size ; i++)
    {
        printf("%d  ",arr[i]);
    }
    printf("\n");

    printf("The element found at the index:%d",(binarysearch(arr,size,target)));
    printf("\n");
    printf("The binarysearch found element is log(n) TC");
}