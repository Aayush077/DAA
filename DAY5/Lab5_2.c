/*
Problem
You are given an array of k linked-lists, each linked-list is sorted in ascending order.
Your task is to merge all the linked-lists into one sorted linked-list and return it.
Examples
 Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation:
1 -&gt; 4 -&gt; 5
1 -&gt; 3 -&gt; 4
2 -&gt; 6
Merging gives 1 -&gt; 1 -&gt; 2 -&gt; 3 -&gt; 4 -&gt; 4 -&gt; 5 -&gt; 6
Output Format
Return the head of the merged sorted linked list.
Requirements &amp; Hints
• Use a priority queue (min-heap) to get the next smallest element efficiently.
• Alternatively, use divide and conquer to merge lists two at a time.
• Handle edge cases: empty lists, single list, lists with one element.
Sample Test Cases
 lists = [[1,2,3],[4,5,6],[7,8,9]] → [1,2,3,4,5,6,7,8,9]
 lists = [[1,4,5],[1,3,4],[2,6]] → [1,1,2,3,4,4,5,6]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparisons = 0;

struct Node
{
    int data;
    struct Node *next;
} *first = NULL;

void create_linkedlist(int arr[], int n)
{
    int i;
    struct Node *t, *last;
    first = (struct Node *)malloc(sizeof(struct Node));
    first->data = arr[0];
    first->next = NULL;
    last = first;
    for (i = 1; i < n; i++)
    {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = arr[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}

void display_LinkedList(struct Node *p)
{
    while (p != NULL)
    {
        printf(" %d", p->data);
        p = p->next;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}

void merge(int arr[], int l, int mid, int h)
{
    int B[500];
    int i = l, j = mid + 1, k = l;

    while (i <= mid && j <= h)
    {
        comparisons++; // Count each comparison
        if (arr[i] < arr[j])
            B[k++] = arr[i++];
        else
            B[k++] = arr[j++];
    }
    for (; i <= mid; i++)
        B[k++] = arr[i++];
    for (; j <= h; j++)
        B[k++] = arr[j++];

    for (i = l; i <= h; i++)
        arr[i] = B[i];
}

int main()
{
    int n, c, x;
    printf("Enter the size: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    create_linkedlist(arr, n);
    display_LinkedList(first);

    mergeSort(arr, 0, n - 1);
    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Total comparisons made: %d\n", comparisons);
}