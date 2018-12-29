#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.c"
#include "stacks.c"


void dfs(int n, Graph *graph, bool **reachable)
{
    int u, i;
    
    bool visited[graph -> V];
    for (i = 0; i < graph -> V; i++)
        visited[i] = false;

    AdjNode *temp;
    Stack *s = createStack();
    push(s, n);

    while (!empty(s))
    {
        u = top(s);
        pop(s);

        if (!visited[u])
        {
            visited[u] = true;
            reachable[n][u] = true;
            temp = graph -> adjList[u];

            while (temp != NULL)
            {
                if (!visited[temp -> v])
                    push(s, temp -> v);
                temp = temp -> next;
            }
        }
    }
}

// Run DFS from every vertex
void compute_reachability(int n, Graph *graph, bool **reachable)
{
    int i;
    for (i = 0; i < n; i++)
        dfs(i, graph, reachable);
}

void show_reachability(bool** reachable, int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        printf("%d -> ", i + 1);
        for (j = 0; j < n; j++)
            if (reachable[i][j])
                printf("%d ", j + 1);
        printf("\n");
    }
}

// int main()
// {
//     int n, m, u, v, wt, i, j;

//     scanf("%d %d", &n, &m);
//     Graph *graph = createGraph(n);

//     for (i = 0; i < m; i++)
//     {
//         scanf("%d %d %d", &u, &v, &wt);
//         addEdge(graph, u - 1, v - 1, wt);
//     }

//     bool **reachable = (bool**) malloc(n * sizeof(bool*));
//     for (i = 0; i < n; i++)
//         reachable[i] = (bool*) malloc(n * sizeof(bool));
    
//     for (i = 0; i < n; i++)
//         for (j = 0; j < n; j++)
//             reachable[i][j] = false;
    
//     compute_reachability(n, graph, reachable);
//     show_reachability(reachable, n);

//     return 0;
// }
