/* Aim of the program: Given an array arr[] of size N, find the prefix sum of the array. 
A prefix sum array is another array prefixSum[] of the same size, such that the value\
 of prefixSum[i] is arr[0] + arr[1] + arr[2] . . . arr[i].

Input Array:    3          4          5          1          2

Output Array: 3          7          12        13        15
*/

#include<stdio.h>
#include<stdlib.h>

int main(){
    int n, i;
    int arr[n];
    int *prefixSum;

    printf("Enter the size of the array: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    FILE *fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    fscanf(fp, "%d", &n);
    if (n <= 0) {
        fclose(fp);
        return 1;
    }
    prefixSum = malloc(n * sizeof(int));
    if (prefixSum == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return 1;
    }

    prefixSum[0] = arr[0];
    for (i = 1; i < n; i++) {
        prefixSum[i] = prefixSum[i - 1] + arr[i];
    }


    printf("Prefix Sum Array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", prefixSum[i]);
    }
    printf("\n");

    
    free(prefixSum);
    fclose(fp);
    return 0;
}