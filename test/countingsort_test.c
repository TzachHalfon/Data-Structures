#include <stdio.h> /* printf */
#include <stdlib.h> /* random */
#include <time.h> /* time */

#include "countingsort.h"

#define ARR_SIZE 5000
#define ARR_RANGE 300

static void CheckIfArrayIsSorted(int*, int size);
static void InitializeArr(int *arr, int size);

int main()
{
	int arr[ARR_SIZE];
    clock_t start ,end;
    InitializeArr(arr, ARR_SIZE);
    start = clock();
    CountingSort(arr,ARR_SIZE);
    end = clock();
    printf("Total time taken by CPU for CountingSort: %ldms\n",(end-start) / (CLOCKS_PER_SEC / 1000));
    CheckIfArrayIsSorted(arr,ARR_SIZE);

    
	InitializeArr(arr, ARR_SIZE);
    start = clock();
    printf("RadixSort status: %d\n",RadixSort(arr,ARR_SIZE));
    end = clock();
    printf("Total time taken by CPU for RadixSort: %ldms\n",(end-start) / (CLOCKS_PER_SEC / 1000));
    CheckIfArrayIsSorted(arr,ARR_SIZE);
    
	return (0);
}

static void InitializeArr(int *arr, int size)
{
    int i = 0;
    srand(time(NULL));
    for(i = 0; i < size; ++i)
    {
        arr[i] = rand() % ARR_RANGE;
    }
}

static void CheckIfArrayIsSorted(int *arr, int size)
{
    int i = 0;
    for(i = 0; i < size - 1; ++i)
    {
        if(arr[i] > arr[i + 1])
        {
            printf ("not sorted!\n");
            printf ("%d %d\n",arr[i],arr[i + 1]);
            return;
        }
    }
    printf ("sorted!\n");
}