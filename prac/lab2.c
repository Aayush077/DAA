/*Write a program to implement Binary Search to give the position of
leftmost appearance of the element in the array being searched. Display the number of
comparisons made while searching.
*/

#include <stdio.h>
#include <stdlib.h>


int binSearchLM(int arr[], int size, int key)
{
    int left = 0, right = size - 1;
    int result = -1; // To store the position of leftmost occurrence

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            result = mid; // Update result and search in the left half
            right = mid - 1;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int main()
{
    int arr[100], n, key, pos;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter %d elements in sorted order: ", n);
    for(int i=0; i<n; i++)
        scanf("%d", &arr[i]);
    printf("Enter element to search: ");
    scanf("%d", &key);
    pos = binSearchLM(arr, n, key);
    if(pos != -1)
        printf("Leftmost position of %d is at index %d\n", key, pos);
    else
        printf("%d not found in the array\n", key);
    return 0;
}