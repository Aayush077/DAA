/*
Aim of the program: Write a program to implement the matrix chain multiplication problem
using M-table &amp; S-table to find optimal parenthesization of a matrix-chain product. Print the
number of scalar multiplications required for the given input.
Note# Dimensions of the matrices can be inputted as row and column values. Validate the
dimension compatibility.
Input:
Enter number of matrices: 4
Enter row and col size of A1: 30 35
Enter row and col size of A2: 35 15
Enter row and col size of A3: 15 5
Enter row and col size of A4: 5 10
Output:
M Table:
0 15750 7875 9375
0 0 2625 4375
0 0 0 750
0 0 0 0
S Table:
0 1 1 3
0 0 2 3
0 0 0 3
0 0 0 0
Optimal parenthesization: ( ( A1 (A2 A3)) A4)
The optimal ordering of the given matrices requires 9375 scalar multiplications.
*/

#include <stdio.h>
#include <limits.h>

#include <stdio.h>
#include <limits.h>

#define MAX 10

void matrixChainOrder(int p[], int n, int m[MAX][MAX], int s[MAX][MAX]) {
    for (int i = 1; i <= n; i++)
        m[i][i] = 0;

    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void printMTable(int m[MAX][MAX], int n) {
    printf("\nM Table:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i > j)
                printf("0\t");
            else
                printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
}

void printSTable(int s[MAX][MAX], int n) {
    printf("\nS Table:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i >= j)
                printf("0\t");
            else
                printf("%d\t", s[i][j]);
        }
        printf("\n");
    }
}

void printParenthesis(int i, int j, int s[MAX][MAX]) {
    if (i == j)
        printf("A%d", i);
    else {
        printf("(");
        printParenthesis(i, s[i][j], s);
        printParenthesis(s[i][j] + 1, j, s);
        printf(")");
    }
}

int main() {
    int n, i, row, col;
    int p[MAX], m[MAX][MAX], s[MAX][MAX];

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        printf("Enter row and col size of A%d: ", i);
        scanf("%d %d", &row, &col);

        if (i == 1)
            p[0] = row;  

        p[i] = col;    
    }

    matrixChainOrder(p, n, m, s);

    printMTable(m, n);
    printSTable(s, n);

    printf("\nOptimal parenthesization: ");
    printParenthesis(1, n, s);

    printf("\nThe optimal ordering of the given matrices requires %d scalar multiplications.\n", m[1][n]);

    return 0;
}
