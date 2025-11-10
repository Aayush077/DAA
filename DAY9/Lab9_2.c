/*
Aim of the program: Write a program to find out the Longest Common Subsequence of two
given strings. Calculate length of the LCS.
Input:

Enter the first string into an array: 10010101
Enter the second string into an array: 010110110

Output:
LCS: 100110
LCS Length: 6
*/

#include <stdio.h>
#include <string.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int lcsLength(char X[], char Y[], int m, int n)
{
    if (m == 0 || n == 0)
        return 0;

    if (X[m - 1] == Y[n - 1])
        return 1 + lcsLength(X, Y, m - 1, n - 1);
    else
        return max(lcsLength(X, Y, m - 1, n), lcsLength(X, Y, m, n - 1));
}

void lcsString(char X[], char Y[], int m, int n, char lcs[])
{
    if (m == 0 || n == 0)
        return;

    if (X[m - 1] == Y[n - 1])
    {
        lcsString(X, Y, m - 1, n - 1, lcs);
        strncat(lcs, &X[m - 1], 1);  
    }
    else
    {
        if (lcsLength(X, Y, m - 1, n) > lcsLength(X, Y, m, n - 1))
            lcsString(X, Y, m - 1, n, lcs);
        else
            lcsString(X, Y, m, n - 1, lcs);
    }
}

int main()
{
    char X[50], Y[50];
    printf("Enter the first string: ");
    scanf("%s", X);
    printf("Enter the second string: ");
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    char lcs[50] = "";
    int length = lcsLength(X, Y, m, n);
    lcsString(X, Y, m, n, lcs);

    printf("\nLCS: %s\n", lcs);
    printf("LCS Length: %d\n", length);

    return 0;
}
