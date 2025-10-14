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

// Node structure definition
struct Node {
    int data;
    struct Node *next;
};


struct Node* create_linkedlist(int arr[], int n) {
    if (n == 0) {
        return NULL;
    }
    
    struct Node *head, *t, *last;
    head = (struct Node *)malloc(sizeof(struct Node));
    head->data = arr[0];
    head->next = NULL;
    last = head;

    for (int i = 1; i < n; i++) {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = arr[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
    return head;
}

/**
 * Displays the elements of a linked list.
 * Pointer to the head of the list.
 */

void display_LinkedList(struct Node *p) {
    printf("[");
    while (p != NULL) {
        printf("%d", p->data);
        if (p->next != NULL) {
            printf(",");
        }
        p = p->next;
    }
    printf("]");
}

/**
 * Frees all the nodes in a linked list to prevent memory leaks.
 * The head of the list to be freed.
 */
void free_list(struct Node* head) {
    struct Node *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

/* --- Core Logic for Merging k Lists (Unchanged) --- */


struct Node* mergeTwoLists(struct Node* l1, struct Node* l2) {
    struct Node temp;
    struct Node* tail = &temp;
    temp.next = NULL;

    while (l1 != NULL && l2 != NULL) {
        if (l1->data < l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    if (l1 != NULL) {
        tail->next = l1;
    } else {
        tail->next = l2;
    }

    return temp.next;
}


struct Node* mergeKLists(struct Node** lists, int k) {
    if (k == 0) {
        return NULL;
    }

    while (k > 1) {
        int new_k = 0;
        for (int i = 0; i < k; i += 2) {
            if (i + 1 < k) {
                lists[new_k] = mergeTwoLists(lists[i], lists[i + 1]);
            } else {
                lists[new_k] = lists[i];
            }
            new_k++;
        }
        k = new_k;
    }

    return lists[0];
}

/**
 * Main function to take user input and run the mergeKLists function.
 */
int main() {
    int k;
    printf("Enter the number of linked lists (k): ");
    scanf("%d", &k);

    if (k <= 0) {
        printf("No lists to merge.\n");
        return 0;
    }

    // Dynamically allocate an array to hold the heads of k lists
    struct Node** lists = (struct Node**)malloc(k * sizeof(struct Node*));
    if (lists == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Loop to get input for each of the k lists
    for (int i = 0; i < k; i++) {
        int n;
        printf("\nEnter the number of elements for list %d: ", i + 1);
        scanf("%d", &n);

        if (n == 0) {
            lists[i] = NULL;
            continue;
        }

        // Dynamically allocate an array for the elements of the current list
        int* arr = (int*)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed for list elements!\n");
            // Free previously allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free_list(lists[j]);
            }
            free(lists);
            return 1;
        }
        
        printf("Enter the %d sorted elements for list %d (space-separated): ", n, i + 1);
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[j]);
        }

        // Create the linked list from the user's array
        lists[i] = create_linkedlist(arr, n);
        
        // Free the temporary integer array as it's no longer needed
        free(arr);
    }

    printf("\n--- Input Lists ---\n");
    for (int i = 0; i < k; i++) {
        printf("List %d: ", i + 1);
        display_LinkedList(lists[i]);
        printf("\n");
    }
    
    // Merge all the lists
    struct Node* merged_head = mergeKLists(lists, k);

    // Display the final result
    printf("\n--- Merged Sorted List ---\n");
    display_LinkedList(merged_head);
    printf("\n");

    // Clean up all dynamically allocated memory
    free_list(merged_head);
    free(lists);
    
    return 0;
}