/*Aim of the program: Given an undirected weighted connected graph G(V, E). Apply
Krushkal’s algorithm to
● Find the minimum spanning tree T(V, E’) and Display the selected edges of G.
● Display total cost of the minimum spanning tree T.
Note# Nodes will be numbered consecutively from 1 to n (user input), and edges will have
varying weight. The weight matrix of the graph can be represented from the user’s input in
the given format. The expected output could be the selected edge and the corresponding cost
of the edge as per the sample output.
Input Format:
● The first line contains two space-separated integers ‘n’ and ‘m’, the number of
nodes and edges in the graph.
● Each line ‘i’ of the ‘m’ subsequent lines contains three space-separated integers ‘u’,
‘v’ and ‘w’, that describe an edge (u, v) and weight ‘w’.*/

#include <stdio.h>

int parent[50];

int find(int i)
{
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionSet(int i, int j)
{
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

// Function to sort edges by weight
void sortEdges(int u[], int v[], int w[], int m)
{
    int i, j;
    for (i = 0; i < m - 1; i++)
    {
        for (j = 0; j < m - i - 1; j++)
        {
            if (w[j] > w[j + 1])
            {
                int temp = w[j];
                w[j] = w[j + 1];
                w[j + 1] = temp;

                temp = u[j];
                u[j] = u[j + 1];
                u[j + 1] = temp;

                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// Function to find MST using Kruskal's Algorithm
void kruskalMST(int u[], int v[], int w[], int n, int m)
{
    int i, edgeCount = 0, totalCost = 0;

    printf("\nSelected Edges in MST:\n");
    for (i = 0; i < m && edgeCount < n - 1; i++)
    {
        int a = find(u[i]);
        int b = find(v[i]);

        if (a != b)
        {
            printf("Edge: %d - %d  Cost: %d\n", u[i], v[i], w[i]);
            totalCost += w[i];
            unionSet(a, b);
            edgeCount++;
        }
    }

    printf("Total Weight of the Spanning Tree: %d\n", totalCost);
}

int main()
{
    int n, m;
    int u[50], v[50], w[50];

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &m);

    printf("Enter each edge as: u v w\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &u[i], &v[i], &w[i]);
    }

    // Initialize parent array here (no separate function)
    for (int i = 1; i <= n; i++)
        parent[i] = i;

    sortEdges(u, v, w, m);
    kruskalMST(u, v, w, n, m);

    return 0;
}
