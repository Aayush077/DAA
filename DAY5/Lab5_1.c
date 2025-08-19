/*
Write a menu driven program to sort a list of elements in ascending order using Quick Sort
technique.
Each choice for the input data has its own disc file. A separate output file can be used for
sorted elements.
After sorting, display the content of the output file along with the number of comparisons.
Based on the partitioning position for each recursive call, conclude whether the input
scenario is either best-case partitioning or worst-case partitioning.

Notes
• The worst-case behavior for Quick Sort occurs when the partitioning routine produces one
subproblem with n-1 elements and one with 0 elements.
• The best-case behavior occurs in the most even possible split, when partitioning produces
two subproblems, each of size no more than n/2.
• Number of elements in each input file should vary from 300 to 500 entries.
Input Files
• For ascending order: Read data from a file “inAsce.dat” having content 10 20 30 40 …,
Store the result in “outQuickAsce.dat”.
• For descending order: Read data from a file “inDesc.dat” having content 90 80 70 60 …,
Store the result in “outQuickDesc.dat”.
• For random data: Read data from a file “inRand.dat” having content 55 66 33 11 44 …,
Store the result in “outQuickRand.dat”.
Sample Input (from file)
MAIN MENU (QUICK SORT)
1. Ascending Data
2. Descending Data
3. Random Data
4. ERROR (EXIT)
Sample Output
Enter option: 1
Before Sorting: Content of the input file
After Sorting: Content of the output file
Number of Comparisons: &lt;value&gt;
Actual Scenario: Best-case or Worst-case

*/
#include <stdio.h>
#include <stdlib.h>

int comparisons = 0; // global counter

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int l, int h)
{
    int pivot = arr[l];
    int i = l;

    for (int j = l + 1; j <= h; j++)
    {
        comparisons++;
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i], &arr[l]); 
    return i;
}

void quickSort(int arr[], int l, int h)
{
    if (l < h)
    {
        int p = partition(arr, l, h);
        quickSort(arr, l, p - 1);
        quickSort(arr, p + 1, h);
    }
}

void readFile(int arr[], int *n, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
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
        exit(1);
    }
    for (int i = 0; i < n; i++)
        fprintf(file, "%d ", arr[i]);
    fclose(file);
}

void displayArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void checkScenario(int n, int pivot)
{
    if (pivot == 0 || pivot == n - 1)
        printf("Actual Scenario: Worst-case partitioning\n");
    else if (pivot == n / 2 || pivot == n / 2 - 1)
        printf("Actual Scenario: Best-case partitioning\n");
    else
        printf("Actual Scenario: Average-case\n");
}

int main()
{
    int arr[500], n, choice;
    char inputFile[50], outputFile[50];

    while (1)
    {
        printf("\nMAIN MENU (QUICK SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. ERROR (EXIT)\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        if (choice == 4)
        {
            printf("Exiting...\n");
            break;
        }

        switch (choice)
        {
        case 1:
            sprintf(inputFile, "inAsce.dat");
            sprintf(outputFile, "outQuickAsce.dat");
            break;
        case 2:
            sprintf(inputFile, "inDesc.dat");
            sprintf(outputFile, "outQuickDesc.dat");
            break;
        case 3:
            sprintf(inputFile, "inRand.dat");
            sprintf(outputFile, "outQuickRand.dat");
            break;
        default:
            printf("Invalid option. Try again.\n");
            continue;
        }

        readFile(arr, &n, inputFile);

        printf("\nBefore Sorting:\n");
        displayArray(arr, n);

        comparisons = 0; 
        quickSort(arr, 0, n - 1);

        writeFile(outputFile, arr, n);

        printf("\nAfter Sorting:\n");
        displayArray(arr, n);

        printf("No. of Comparisons: %d\n", comparisons);

        int pivot = partition(arr, 0, n - 1);
        checkScenario(n, pivot);
    }

    return 0;
}
