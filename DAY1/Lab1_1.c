/*Aim of the program: Write a program to find out the second smallest and second largest element stored in an array of n integers.

Input: Size of the array is ‘n’ and read ‘n’ number of elements from a file.

Output: Second smallest, Second largest*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(){
    FILE *fp;
    int n, i, f_smallest, s_smallest, f_largest, s_largest;
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(fp, "%d", &n);
    if (n < 2) {
        printf("Array must contain at least two elements.\n");
        fclose(fp);
        return 1;
    }  
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return 1;
    }
    for (i = 0; i < n; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);
    f_smallest = s_smallest = INT_MAX; 
    f_largest = s_largest = INT_MIN;

    for (i = 0; i < n; i++) {
        if (arr[i] < f_smallest) {
            s_smallest = f_smallest;
            f_smallest = arr[i];
        } else if (arr[i] < s_smallest && arr[i] != f_smallest) {
            s_smallest = arr[i];
        }

        if (arr[i] > f_largest) {
            s_largest = f_largest;
            f_largest = arr[i];
        } else if (arr[i] > s_largest && arr[i] != f_largest) {
            s_largest = arr[i];
        }
    }
    printf("Second smallest: %d\n", s_smallest);
    printf("Second largest: %d\n", s_largest);
    free(arr);
 
    return 0;
}