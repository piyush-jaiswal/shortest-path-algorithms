#include <stdio.h>
#include <stdlib.h>

typedef struct adjNode
{
    int v;
    int w;
    struct adjNode *next;
}AdjNode;

typedef struct graph
{
    int V;
    AdjNode **adjList;
}Graph;

Graph* createGraph(int v)
{
    Graph *graph = (Graph*) malloc (sizeof(Graph));
    graph -> V = v;
    graph -> adjList = (AdjNode**) malloc (v * sizeof(AdjNode*));

    int i;
    for (i = 0; i < graph -> V; i++)
        graph -> adjList[i] = NULL;
    return graph;
}

AdjNode* createNode(int v, int wt)
{
    AdjNode *n = (AdjNode*) malloc(sizeof(AdjNode));
    n -> v = v;
    n -> w = wt;
    n -> next = NULL;
    return n;
}

void addEdge(Graph* graph, int u, int v, int wt)
{
    AdjNode* n = createNode(v, wt);

    // Add node at the start of the list
    n -> next = graph -> adjList[u];
    graph -> adjList[u] = n;
}

// int main()
// {
//     int n, m, u, v, wt, i;
//     AdjNode* temp;

//     scanf("%d %d", &n, &m);
//     Graph *g = createGraph(n);

//     for (i = 0; i < m; i++)
//     {
//         scanf("%d %d %d", &u, &v, &wt);
//         addEdge(g, u - 1, v - 1, wt);
//     }

//     for (i = 0; i < g -> V; i++)
//     {
//         printf("%d -> ", i);
//         temp = g -> adjList[i];
//         while (temp != NULL)
//         {
//             printf("%d(%d) ", temp -> v, temp -> w);
//             temp = temp -> next;
//         }
//         printf("\n");
//     }
// }
