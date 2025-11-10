/*
Consider an undirected graph where each edge weights 2 units. Each of
the nodes is labeled consecutively from 1 to n. The user will input a list of edges for describing
an undirected graph. After representation of the graph, from a given starting position
● Display the breadth-first search traversal.
● Determine and display the shortest distance to each of the other nodes using the breadth
first search algorithm. Return an array of distances from the start node in node number
order. If a node is unreachable, return -1 for that node.
Input Format:
● The first line contains two space-separated integers ‘n’ and ‘m’, the number of nodes and
edges in the graph.
● Each line ‘i’ of the ‘m’ subsequent lines contains two space-separated integers ‘u’ and
‘v’, that describe an edge between nodes ‘u’ and ‘v’.
● The last line contains a single integer ‘s’, the node number to start from.
Output Format:
● The first line shows the result of the BFS traversal.
● The last line shows an array of distances from node ‘s’ to all other nodes.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX];      // adjacency matrix
int visited[MAX];
int distanceArr[MAX];
int queue[MAX];
int front = -1, rear = -1;

void enqueue(int x)
{
    if (rear == MAX - 1)
        return;
    if (front == -1)
        front = 0;
    queue[++rear] = x;
}

int dequeue()
{
    if (front == -1 || front > rear)
        return -1;
    return queue[front++];
}

void BFS(int start, int n)
{
    int i, node;
    for (i = 1; i <= n; i++)
    {
        visited[i] = 0;
        distanceArr[i] = -1; // -1 means unreachable
    }

    visited[start] = 1;
    distanceArr[start] = 0;
    enqueue(start);

    printf("BFS Traversal: ");

    while (front <= rear)
    {
        node = dequeue();
        printf("%d ", node);

        for (i = 1; i <= n; i++)
        {
            if (adj[node][i] == 1 && visited[i] == 0)
            {
                visited[i] = 1;
                distanceArr[i] = distanceArr[node] + 2; // each edge = 2 units
                enqueue(i);
            }
        }
    }
    printf("\n");
}

int main()
{
    int n, m;
    printf("Enter number of nodes and edges: ");
    scanf("%d %d", &n, &m);

    int u, v;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1; // undirected graph
    }

    int s;
    printf("Enter starting node: ");
    scanf("%d", &s);

    BFS(s, n);

    printf("Shortest distances from node %d:\n", s);
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", distanceArr[i]);
    }
    printf("\n");

    return 0;
}
