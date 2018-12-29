#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "reachability_preprocessing.c"
// #include "binary_heap.c"
#include "d_ary_heap.c"

int dijkstra(Graph *g, int s, int t, bool **reachable)
{
    int n, i, u, v, distance;
    n = g -> V;
    AdjNode **adj = g -> adjList;
    int *dist = (int*) malloc(n * sizeof(int));
    AdjNode *temp;

    for (i = 0; i < n; i++)
        dist[i] = INT_MAX;
    dist[s] = 0;
    
    // BinaryHeap_pq *p = (BinaryHeap_pq*) malloc(sizeof(BinaryHeap_pq));
    // initialize_pq(p, n);
    D_aryHeap_pq *p = (D_aryHeap_pq*) malloc(sizeof(D_aryHeap_pq));
    initialize_pq(p, n, 4);
    insertNode(p, s, 0);

    while(!isEmpty(p))
    {
        u = extractMin(p);

        if (u == t)
            return dist[t];
        
        temp = adj[u];
        while (temp != NULL)
        {
            v = temp -> v;

            // Idea - insert into priority queue only if you can reach the destination from there
            if (reachable[v][t])
            {
                distance = dist[u] + temp -> w;

                if (dist[v] > distance)
                {
                    dist[v] = distance;
                    insertNode(p, v, distance);
                }
            }
            temp = temp -> next;
        }
    }

    return -1;
}

int main()
{
    int n, m, u, v, wt, i, j, s, t;

    scanf("%d %d", &n, &m);
    Graph *graph = createGraph(n);

    for (i = 0; i < m; i++)
    {
        scanf("%d %d %d", &u, &v, &wt);
        addEdge(graph, u - 1, v - 1, wt);
    }
    scanf("%d %d", &s, &t);
    s--;
    t--;

    bool **reachable = (bool**) malloc(n * sizeof(bool*));
    for (i = 0; i < n; i++)
        reachable[i] = (bool*) malloc(n * sizeof(bool));
    
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            reachable[i][j] = false;
    
    compute_reachability(n, graph, reachable);
    // show_reachability(reachable, n);

    printf("%d\n", dijkstra(graph, s, t, reachable));
    return 0;
}
