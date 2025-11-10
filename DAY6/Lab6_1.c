/*
Aim of the program: Write a program to find the maximum profit nearest to but not exceeding the given knapsack capacity using the Fractional Knapsack algorithm.
Notes# Declare a structure ITEM having data members item_id, item_profit, item_weight and profit_weight_ratio. Apply heap sort technique to sort the items in non-increasing order, according to their profit /weight.
Input:
Enter the number of items: 3
Enter the profit and weight of item no 1: 27 16
Enter the profit and weight of item no 2: 14 12
Enter the profit and weight of item no 3: 26 13
Enter the capacity of knapsack:18


Output:
Item No ​profit​ ​Weight ​​Amount to be taken
3 ​ 26.000000 ​13.000000​​1.000000
1 ​ 27.000000 ​16.000000 ​​0.312500
2 ​14.000000 ​12.000000 ​​0.000000
Maximum profit: 34.437500
*/

#include<stdio.h>
#include<stdlib.h>

struct ITEM
{
        int item_id;
        float item_profit;
        float item_weight;
        float profit_weight_ratio;
};

int compare(const void *a, const void *b)
{
    struct ITEM *item1 = (struct ITEM *)a;
    struct ITEM *item2 = (struct ITEM *)b;
    return (item2->profit_weight_ratio - item1->profit_weight_ratio);
}

int main()
{
    int n, i;
    float capacity, total_profit = 0.0;
    struct ITEM *items;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    items = (struct ITEM *)malloc(n * sizeof(struct ITEM));

    for (i = 0; i < n; i++)
    {
        items[i].item_id = i + 1;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);


    qsort(items, n, sizeof(struct ITEM), compare);

    for (i = 0; i < n; i++)
    {
        if (items[i].item_weight <= capacity)
        {
            total_profit += items[i].item_profit;
            capacity -= items[i].item_weight;
        }
        else
        {
            total_profit += items[i].profit_weight_ratio * capacity;
            break;
        }
    }

    printf("Maximum profit: %.6f\n", total_profit);

    free(items);
    return 0;
}