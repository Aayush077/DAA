/*1.3 Aim of the program: Write a program to read ‘n’ integers from a file that must
contain some duplicate values and store them into an array.Perform the following operations on the array.

a)Find out the total number of duplicate elements.

b)Find out the most repeating element in the array.

Input:

Enter how many numbers you want to read from file: 15

Output:

The content of the array: 10 40 35 47 68 22 40 10 98 10 50 35 68 40 10

Total number of duplicate values = 4

The most repeating element in the array = 10*/

#include <stdio.h>

int main() {
    int arr[100], n, i, j;
    int visited[100] = {0};
    int count = 0;
    int mostRepeated, max_F = 0;

    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Enter how many numbers you want to read from file: ");
    scanf("%d", &n);

    // Read n numbers from file
    for (i = 0; i < n; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);

    // Display the array
    printf("\nThe content of the array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    // Find distinct duplicates and most repeating element
    for (i = 0; i < n; i++) {
        if (visited[i])
            continue;

        int freq = 1;
        for (j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                freq++;
                visited[j] = 1;  // mark as visited
            }
        }

        if (freq > 1)
            count++;  // count as one duplicate element

        if (freq > max_F) {
            max_F = freq;
            mostRepeated = arr[i];
        }
    }

    printf("\n\nTotal number of duplicate values = %d", count);
    printf("\nThe most repeating element in the array = %d\n", mostRepeated);

    return 0;
}
