/*
Let n be a positive integer. We want to reduce n to 1 by applying a
sequence of simple operations on n. The operations permitted are division of n by two (provided
that n is even), and addition of a small positive or negative integer to n. Your objective is to
reach the final goal 1 with as few applications of these operations as possible
a) Assume that the only operations permitted are decrement (by 1) and division by 2
(allowed if and only if n is even). For example, consider this reduction of 125 to 1, which
uses 12 steps: 125 → 124 → 62 → 31 → 30 → 15 → 14 → 13 → 12 → 6 → 3 → 2 → 1.
This sequence is not optimal. An obvious greedy strategy is based on the fact that
division by 2 produces the best possible local reduction. However, if n is odd, this
operation is not allowed, so decrement n to make it even, and then divide by 2. The
optimal solution involves 11 steps only:
125 → 124 → 62 → 31 → 30 → 15 → 14 → 7 → 6 → 3 → 2 → 1.
Implement this greedy algorithm in a function greedy1
b) Now, suppose that besides decrement by 1 and division by 2, you are permitted to
increment n by 1. A greedy approach in this case is to keep on dividing n by 2 so long as
it remains even. Once n becomes odd, compute n − 1 and n + 1, and choose the one
which has a larger number of factors of 2. This is illustrated by the next example. This
reduction has nine steps.
125 → 124 → 62 → 31 → 32 → 16 → 8 → 4 → 2 → 1.
A long sequence of consecutive increments/decrements does not help:
125 → 126 → 127 → 128 → 64 → 32 → 16 → 8 → 4 → 2 → 1.
Changing 125 to 128 by increments is not helpful. A shorter sequence is achieved at a
reduced level by one increment of 31 to 32. This greedy strategy fails only for n = 3. The
greedy reduction is 3 → 4 → 2 → 1, whereas the optimal reduction is 3 → 2 → 1. Write
a function greedy2 to implement these observations. 
*/
#include<stdio.h>


int countFactorsOf2(int n) {
    int count = 0;
    while (n % 2 == 0) {
        n /= 2;
        count++;
    }
    return count;
}

int greedy2(int n) {
    int steps = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            if (n == 3 || countFactorsOf2(n - 1) >= countFactorsOf2(n + 1)) {
                n -= 1;
            } else {
                n += 1;
            }
        }
        steps++;
    }
    return steps;
}


int main() {
    int n;
    printf("Enter a +ve integer: ");
    scanf("%d", &n);
    int steps = greedy2(n);
    printf("Minimum steps to reduce %d to 1: %d\n", n, steps);
    return 0;
}