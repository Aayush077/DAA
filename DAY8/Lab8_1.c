/*
Aim of the program:
Write a program to implement the 0/1 Knapsack Problem using Dynamic Programming.
Print the table used for computation (DP table), the selected items, and the maximum profit.
Input:
Enter number of items: 4
Enter weights of items: 2 3 4 5
Enter values of items: 3 4 5 6
Enter knapsack capacity: 5
Output:
DP Table:
0 0 0 0 0 0
0 3 3 3 3 3
0 3 4 4 7 7
0 3 4 5 7 8
0 3 4 5 7 8
Selected items: Item2, Item1
Maximum Profit: 7
*/


#include <stdio.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void buildDPTable(int n, int W, int wt[], int val[], int dp[][100])
{
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i] <= w)
                dp[i][w] = max(val[i] + dp[i - 1][w - wt[i]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
}

void tracebackItems(int n, int W, int wt[], int dp[][100], int selected[])
{
    for (int i = 1; i <= n; i++)
        selected[i] = 0;

    int i = n, w = W;
    while (i > 0 && w > 0)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            selected[i] = 1;
            w -= wt[i];
        }
        i--;
    }
}

int main()
{
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);

    int wt[100], val[100], dp[100][100], selected[100];

    printf("Enter weights of items: ");
    for (int i = 1; i <= n; i++)
        scanf("%d", &wt[i]);

    printf("Enter values of items: ");
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    buildDPTable(n, W, wt, val, dp);

    // Print DP Table
    printf("\nDP Table:\n");
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
            printf("%d ", dp[i][w]);
        printf("\n");
    }

    tracebackItems(n, W, wt, dp, selected);

    printf("\nSelected items: ");
    int first = 1;
    for (int i = n; i > 0; i--)
    {
        if (selected[i])
        {
            if (!first)
                printf(", ");
            printf("Item%d", i);
            first = 0;
        }
    }

    printf("\nMaximum Profit: %d\n", dp[n][W]);

    return 0;
}
