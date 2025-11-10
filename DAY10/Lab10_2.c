/*Aim of the program: We represent integers as the sum of Fibonacci numbers. In other
words, instead of an array of bits, we keep an array of fits, where the ith least significant fit
indicates whether the sum includes the ith Fibonacci number Fi.
For example, the fitstring 101110 represents the number F6 + F4 + F3 + F2 = 8 + 3 + 2 + 1 =
14. Write a program to increment and decrement a single fitstring in constant amortized time.
[Hint: Most numbers can be represented by more than one fitstring]*/

#include <stdio.h>
#include <string.h>

// Fibonacci sequence up to F50 (more than enough)
long long fib[50];

// Generate Fibonacci numbers F1 = 1, F2 = 2, ...
void generateFibonacci() {
    fib[1] = 1;
    fib[2] = 2;
    for (int i = 3; i < 50; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
}

// Convert fitstring (MSB first) → integer
long long fitToDecimal(char fit[]) {
    int len = strlen(fit);
    long long value = 0;
    for (int i = 0; i < len; i++) {
        if (fit[i] == '1')
            value += fib[len - i];
    }
    return value;
}

// Convert integer → normalized fitstring (Zeckendorf representation)
void decimalToFit(long long value, char fit[]) {
    int i, index = 0;
    char temp[100] = {0};

    // find largest Fibonacci ≤ value
    for (i = 49; i >= 1; i--) {
        if (fib[i] <= value)
            break;
    }

    // greedy approach
    for (int j = i; j >= 1; j--) {
        if (fib[j] <= value) {
            temp[index++] = '1';
            value -= fib[j];
            j--; // skip next Fibonacci to avoid consecutive 1s
        } else {
            temp[index++] = '0';
        }
    }
    temp[index] = '\0';
    strcpy(fit, temp);
}

// Main function
int main() {
    char fit[100];
    int choice;

    generateFibonacci();

    printf("Enter fitstring (MSB first): ");
    scanf("%s", fit);

    long long num = fitToDecimal(fit);

    printf("\n1. Increment\n2. Decrement\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
        num++;
    else if (choice == 2)
        num--;
    else {
        printf("Invalid choice!\n");
        return 0;
    }

    if (num < 0) {
        printf("\nCannot decrement below zero!\n");
        return 0;
    }

    decimalToFit(num, fit);
    printf("\nUpdated fitstring: %s\n", fit);

    return 0;
}
