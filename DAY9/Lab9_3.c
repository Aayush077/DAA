/*
Aim of the program: Given a directed weighted graph G (V, E) where weight indicates
distance. Vertices will be numbered consecutively from 1 to n (user input), and edges will
have varying distances or lengths.
● Determine the length of the shortest path between every pair of vertices using Floyd-
Warshall’s algorithm.
● Display the intermediate vertices on the shortest-path from the given pair of vertices
(u,v).
Note# The graph G can be read from an input file “inDiAdjMat2.dat” that contains cost
adjacency matrix. The expected output could be a shorted-path weight matrix and the path
consisting of intermediate vertices.
*/
#include <stdio.h>
#define MAX 20
#define INF 9999

int n;
int cost[MAX][MAX], path[MAX][MAX];

// Recursive function to compute shortest distance
int floydRecursive(int i, int j, int k)
{
    if (k == 0)
        return cost[i][j];

    int withoutK = floydRecursive(i, j, k - 1);
    int withK = floydRecursive(i, k - 1, k - 1) + floydRecursive(k - 1, j, k - 1);

    if (withK < withoutK)
    {
        path[i][j] = k - 1;
        return withK;
    }
    else
        return withoutK;
}

// Function to print the shortest path
void printPath(int u, int v)
{
    if (path[u][v] == -1)
        return;
    int k = path[u][v];
    printPath(u, k);
    printf("-->%d", k + 1);
    printPath(k, v);
}

int main()
{
    FILE *fp;
    fp = fopen("inDiAdjMat2.dat", "r");
    if (fp == NULL)
    {
        printf("Error: Cannot open file!\n");
        return 0;
    }

    printf("Number of Vertices: ");
    scanf("%d", &n);

    // Read matrix from file
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            fscanf(fp, "%d", &cost[i][j]);
            if (i != j && cost[i][j] == 0)
                cost[i][j] = INF;
        }

    fclose(fp);

    // Initialize path matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            path[i][j] = -1;

    // Compute shortest paths recursively
    int dist[MAX][MAX];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = floydRecursive(i, j, n);

    // Print shortest path matrix
    printf("\nShortest Path Weight Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] >= INF)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }

    int u, v;
    printf("\nEnter the source and destination vertex: ");
    scanf("%d %d", &u, &v);
    u--; v--;

    if (dist[u][v] >= INF)
        printf("No path exists between %d and %d\n", u + 1, v + 1);
    else
    {
        printf("Shortest Path from vertex %d to vertex %d: %d", u + 1, v + 1, u + 1);
        printPath(u, v);
        printf("-->%d", v + 1);
        printf("\nPath weight: %d\n", dist[u][v]);
    }

    return 0;
}
