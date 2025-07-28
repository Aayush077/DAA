/*Aim of the program: Write a program to find out the second smallest and second largest element stored in an array of n integers.

Input: Size of the array is 'n' and read 'n' number of elements from a file.

Output: Second smallest, Second largest*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int* readFromFile(const char* filename, int* n) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

    fscanf(fp, "%d", n);
    if (*n < 2) {
        printf("Array must contain at least two elements.\n");
        fclose(fp);
        return NULL;
    }

    int *arr = (int *)malloc(*n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < *n; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);
    return arr;
}

int sSmallest(int arr[], int n) {
    int f_smallest = INT_MAX, s_smallest = INT_MAX;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] < f_smallest) {
            s_smallest = f_smallest;
            f_smallest = arr[i];
        } else if (arr[i] < s_smallest && arr[i] != f_smallest) {
            s_smallest = arr[i];
        }
    }
    return s_smallest;
}

int sLargest(int arr[], int n) {
    int f_largest = INT_MIN, s_largest = INT_MIN;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > f_largest) {
            s_largest = f_largest;
            f_largest = arr[i];
        } else if (arr[i] > s_largest && arr[i] != f_largest) {
            s_largest = arr[i];
        }
    }
    return s_largest;
}

void display(int secondSmallest, int secondLargest) {
    printf("Second smallest: %d\n", secondSmallest);
    printf("Second largest: %d\n", secondLargest);
}

int main() {
    int n;
    int *arr = readFromFile("input.txt", &n);
    
    if (arr == NULL) {
        return 1;
    }
    
    int secondSmallest = sSmallest(arr, n);
    int secondLargest = sLargest(arr, n);

    display(secondSmallest, secondLargest);
    
    free(arr);
    return 0;
}
