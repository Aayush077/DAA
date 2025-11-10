/*Aim of the program: Given a directed graph G (V, E) and a starting vertex ‘s’.
● Determine the lengths of the shortest paths from the starting vertex ‘s’ to all other
vertices in the graph G using Dijkstra’s Algorithm.
● Display the shortest path from the given source ‘s’ to all other vertices.
Note# Nodes will be numbered consecutively from 1 to n (user input), and edges will have
varying distances or lengths. The graph G can be read from an input file “inDiAdjMat1.dat”
that contains non-negative cost adjacency matrix. The expected output could be as per the
sample format.*/

#include <stdio.h>
#include <limits.h>

#define MAX 50
#define INF 9999

void dijkstra(int n, int cost[MAX][MAX], int source, int dist[], int parent[])
{
    int visited[MAX] = {0};

    for (int i = 1; i <= n; i++)
    {
        dist[i] = cost[source][i];
        parent[i] = (cost[source][i] != INF && i != source) ? source : -1;
    }

    dist[source] = 0;
    visited[source] = 1;

    for (int count = 1; count < n; count++)
    {
        int u = -1;
        int min = INF;
        for (int i = 1; i <= n; i++)
        {
            if (!visited[i] && dist[i] < min)
            {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 1; v <= n; v++)
        {
            if (!visited[v] && cost[u][v] != INF && dist[u] + cost[u][v] < dist[v])
            {
                dist[v] = dist[u] + cost[u][v];
                parent[v] = u;
            }
        }
    }
}

void printPath(int v, int parent[])
{
    if (parent[v] == -1)
        return;
    printPath(parent[v], parent);
    printf("->%d", v);
}

int main()
{
    int n, source;
    int cost[MAX][MAX];

    FILE *fp = fopen("inDiAdjMat1.dat", "r");
    if (!fp)
    {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);

    printf("Enter the Source Vertex: ");
    scanf("%d", &source);

    // Read adjacency matrix from file
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            fscanf(fp, "%d", &cost[i][j]);
            if (cost[i][j] == 0 && i != j)
                cost[i][j] = INF; // replace 0 with INF except diagonal
        }
    }
    fclose(fp);

    int dist[MAX], parent[MAX];
    dijkstra(n, cost, source, dist, parent);

    printf("\nSource Destination Cost Path\n");
    for (int i = 1; i <= n; i++)
    {
        printf("%d %d ", source, i);
        if (dist[i] >= INF)
        {
            printf("INF No path\n");
        }
        else
        {
            printf("%d ", dist[i]);
            if (i == source)
            {
                printf("-\n");
            }
            else
            {
                printf("%d", source);
                printPath(i, parent);
                printf("\n");
            }
        }
    }

    return 0;
}
