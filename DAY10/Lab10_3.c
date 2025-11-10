/*
Aim of the program: we want to store a big binary counter in an array A. All the entries start
at 0 and at each step we will be simply incrementing the counter. Let’s say our cost model is:
whenever we increment the counter, we pay 1 for every bit we need to flip. Now we not only
wish to increment a counter but also to reset it to 0 (i.e., make all bits in it 0). Counting the
time to examine or modify a bit as θ(1) show how to implement a counter as an array of bits
so that any sequence of n INCREMENT and RESET operations takes O(n) time on an
initially zero counter. (Hint: Keep a pointer to the high-order 1.)
*/
#include <stdio.h>

#define MAX 50

void printCounter(int counter[], int n) {
    for (int i = n - 1; i >= 0; i--)
        printf("%d", counter[i]);
    printf("\n");
}

void incrementCounter(int counter[], int *high, int n) {
    int i = 0;
    while (i < n) {
        if (counter[i] == 0) {
            counter[i] = 1;
            if (i > *high)
                *high = i; // update high-order 1 pointer
            break;
        } else {
            counter[i] = 0;
            i++;
        }
    }
}

// Reset operation
void resetCounter(int counter[], int *high) {
    for (int i = 0; i <= *high; i++)
        counter[i] = 0;
    *high = -1; // reset high-order 1 pointer
}

int main() {
    int counter[MAX] = {0};
    int n, high = -1;
    int choice, steps;

    printf("Enter the number of bits in the counter (max %d): ", MAX);
    scanf("%d", &n);

    printf("\nInitial Counter: ");
    printCounter(counter, n);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Increment Counter\n");
        printf("2. Reset Counter\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter how many times to increment: ");
            scanf("%d", &steps);
            for (int i = 0; i < steps; i++) {
                incrementCounter(counter, &high, n);
                printf("After increment %d: ", i + 1);
                printCounter(counter, n);
            }
        } 
        else if (choice == 2) {
            resetCounter(counter, &high);
            printf("Counter reset to: ");
            printCounter(counter, n);
        } 
        else if (choice == 3) {
            printf("Exiting...\n");
            break;
        } 
        else {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}