/*Aim of the program: Given an undirected weighted connected graph G(V, E) and starring
vertex ‘s’. Maintain a Min-Priority Queue ‘Q’ from the vertex set V and apply Prim’s
algorithm to
● Find the minimum spanning tree T(V, E’). Display the cost adjacency matrix of ‘T’.
● Display total cost of the minimum spanning tree T.
Note# Nodes will be numbered consecutively from 1 to n (user input), and edges will have
varying weight. The graph G can be read from an input file “inUnAdjMat.dat” that contains
cost adjacency matrix. The expected output could be displayed as the cost adjacency matrix
of the minimum spanning tree and total cost of the tree.

Content of the input file “inUnAdjMat.dat” could be
0 4 0 0 0 0 0 8 0
4 0 8 0 0 0 0 11 0
0 8 0 7 0 4 0 0 2
0 0 7 0 9 14 0 0 0
0 0 0 9 0 10 0 0 0
0 0 4 14 10 0 2 0 0
0 0 0 0 0 2 0 1 6
8 11 0 0 0 0 1 0 7
0 0 2 0 0 0 6 7 0
Input:
Enter the Number of Vertices: 9
Enter the Starting Vertex: 1
Output:
0 4 0 0 0 0 0 8 0
4 0 0 0 0 0 0 0 0
0 0 0 7 0 4 0 0 2
0 0 7 0 9 0 0 0 0
0 0 0 9 0 0 0 0 0
0 0 4 0 0 0 2 0 0
0 0 0 0 0 2 0 1 0
8 0 0 0 0 0 1 0 0
0 0 2 0 0 0 0 0 0
Total Weight of the Spanning Tree: 37*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 20

int cost[MAX][MAX], n;

int minKey(int key[], int mstSet[])
{
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < n; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void primMST(int start)
{
    int parent[MAX], key[MAX], mstSet[MAX];
    int mst[MAX][MAX];
    int totalCost = 0;

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
        parent[i] = -1;
        for (int j = 0; j < n; j++)
            mst[i][j] = 0;
    }

    key[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (cost[u][v] && mstSet[v] == 0 && cost[u][v] < key[v]) {
                parent[v] = u;
                key[v] = cost[u][v];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (parent[i] != -1) {
            mst[i][parent[i]] = cost[i][parent[i]];
            mst[parent[i]][i] = cost[i][parent[i]];
            totalCost += cost[i][parent[i]];
        }
    }

    printf("\nCost Adjacency Matrix of MST:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", mst[i][j]);
        printf("\n");
    }

    printf("Total Weight of the Spanning Tree: %d\n", totalCost);
}

int main()
{
    FILE *fp;
    int start;

    fp = fopen("inUnAdjMat.dat", "r");
    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);

    printf("Enter the Starting Vertex: ");
    scanf("%d", &start);
    start--; 

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(fp, "%d", &cost[i][j]);

    fclose(fp);

    primMST(start);

    return 0;
}
