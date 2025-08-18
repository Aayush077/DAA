/*
Aim of the program: Write a menu driven program to sort
list of array elements using Merge Sort technique and calculate the execution
time only to sort the elements.  Count the number of comparisons.

Note#   
To calculate execution time, assume that single
program is under execution in the CPU.
●   
Number of elements in each input file should vary from 300 to 500
entries.
●   
For ascending order: Read data from a file “inAsce.dat” having
content 10 20 30 40….., Store the result in “outMergeAsce.dat”.
●   
For descending order: Read data from a file “inDesc.dat” having
content 90 80 70 60…., Store the result in “outMergeDesc.dat”.
●   
For random data: Read data from a file
“inRand.dat” having content 55 66 33 11 44 …, Store the result in
“outMergeRand.dat”
Sample Input from file:
MAIN MENU (MERGE SORT)
1. Ascending Data
2. Descending Data
3. Random Data
4. ERROR (EXIT)
Output:
Enter option: 1
Before Sorting: Content of the input
file
After Sorting: Content of the output
file
Number of Comparisons: Actual Execution
Time: lapse time in nanosecond
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

long long comparisons = 0; // Global comparison counter

void merge(int arr[], int l, int mid, int h)
{
    int B[500]; // temp array
    int i = l, j = mid + 1, k = l;

    while (i <= mid && j <= h)
    {
        comparisons++; // Count each comparison
        if (arr[i] < arr[j])
            B[k++] = arr[i++];
        else
            B[k++] = arr[j++];
    }
    for ( ; i <= mid; i++)
        B[k++] = arr[i++];
    for ( ; j <= h; j++)
        B[k++] = arr[j++];

    for (i = l; i <= h; i++)
        arr[i] = B[i];
}

void mergeSort(int arr[], int l, int h)
{
    if (l < h)
    {
        int mid = (l + h) / 2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, h);
        merge(arr, l, mid, h);
    }
}

void readFile(int arr[], int *n, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    *n = 0;
    while (fscanf(file, "%d", &arr[*n]) == 1)
        (*n)++;
    fclose(file);
}

void writeFile(const char *filename, int arr[], int n)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
}

void displayArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[500], n, option;
    char inputFile[50], outputFile[50];

    printf("MAIN MENU (MERGE SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. ERROR (EXIT)\n");
    printf("Enter option: ");
    scanf("%d", &option);

    switch (option)
    {
        case 1:
            sprintf(inputFile, "inAsce.dat");
            sprintf(outputFile, "outMergeAsce.dat");
            break;
        case 2:
            sprintf(inputFile, "inDesc.dat");
            sprintf(outputFile, "outMergeDesc.dat");
            break;
        case 3:
            sprintf(inputFile, "inRand.dat");
            sprintf(outputFile, "outMergeRand.dat");
            break;
        default:
            printf("Exiting...\n");
            return 0;
    }

    readFile(arr, &n, inputFile);

    printf("Before Sorting:\n");
    displayArray(arr, n);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    comparisons = 0; // Reset comparison counter
    mergeSort(arr, 0, n - 1);

    clock_gettime(CLOCK_MONOTONIC, &end);

    long long timeTaken = (end.tv_sec - start.tv_sec) * 1000000000LL +
                          (end.tv_nsec - start.tv_nsec);

    writeFile(outputFile, arr, n);

    printf("After Sorting:\n");
    displayArray(arr, n);
    printf("Number of Comparisons: %lld\n", comparisons);
    printf("Actual Execution Time: %lld nanoseconds\n", timeTaken);

    return 0;
}
