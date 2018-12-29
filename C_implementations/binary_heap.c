#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node_dist
{
    int v;
    long long dist;
}Node_dist;

typedef struct binaryHeap_pq
{
    int no_of_elements;
    Node_dist *queue;
    int *positions;     // Keeps track of the positions of the node in the queue.
}BinaryHeap_pq;

void initialize_pq(BinaryHeap_pq *p, int n)
{
  int i;
  p -> no_of_elements = 0;
  p -> queue = (Node_dist*) malloc(n * sizeof(Node_dist));
  p -> positions = (int*) malloc((n + 1) * sizeof(int));

  for (i = 0; i < n + 1; i++)
    p -> positions[i] = -1;
}

int parent(int p)
{
  return (p - 1) / 2;
}

int left(int p)
{
  return p*2 + 1;
}

int right(int p)
{
  return p*2 + 2;
}

void swap(BinaryHeap_pq *pq, int x, int y)
{
  int pos1, pos2; 
  pos1 = pq -> queue[x].v;
  pos2 = pq -> queue[y].v;

  Node_dist temp = pq -> queue[x];
  pq -> queue[x] = pq -> queue[y];
  pq -> queue[y] = temp;

  // Changing the positions in the position array
  pq -> positions[pos1] = y;
  pq -> positions[pos2] = x;
}

void min_heapify(BinaryHeap_pq *pq, int node)
{
  int l, r, smallest;

  l = left(node);
  r = right(node);
  smallest = node;

  if (l < pq -> no_of_elements && pq -> queue[l].dist < pq -> queue[smallest].dist)
    smallest = l;
  if (r < pq -> no_of_elements && pq -> queue[r].dist < pq -> queue[smallest].dist)
    smallest = r;

  if (smallest != node)
  {
    swap(pq, node, smallest);
    min_heapify(pq, smallest);
  }
}

void build_minheap(BinaryHeap_pq *pq)
{
    int i;
    for (i = pq -> no_of_elements / 2; i >=0; i--)
    min_heapify(pq, i);
}

void deleteNode(BinaryHeap_pq *pq, int pos)
{
    swap(pq, pos, pq -> no_of_elements - 1);
    pq -> no_of_elements--;
    min_heapify(pq, pos);
}

// Returns the node with lowest dist value
int extractMin(BinaryHeap_pq *pq)
{
    int node = pq -> queue[0].v;
    deleteNode(pq, 0);
    return node;
}

void min_upheap(BinaryHeap_pq *pq, int node)
{
  int par = parent(node);

  if (par >= 0 &&  pq -> queue[node].dist < pq -> queue[par].dist)
  {
    swap(pq, node, par);
    min_upheap(pq, par);
  }
}

void changePriority(BinaryHeap_pq *pq, int node, int val)
{
    int pos = pq -> positions[node];
    pq -> queue[pos].dist = val;
    min_upheap(pq, pos);      // The value at pos can only be decreased
}

// Insert node takes care of decrease priority
void insertNode(BinaryHeap_pq *p, int v, int d)
{
  if (p -> positions[v] != -1)
  {
    changePriority(p, v, d);
    return;
  }

  Node_dist temp;
  temp.v = v;
  temp.dist = d;
  p -> queue[p -> no_of_elements] = temp;
  p -> positions[v] = p -> no_of_elements;
  p -> no_of_elements ++;
  min_upheap(p, p -> no_of_elements - 1);
}

bool isEmpty(BinaryHeap_pq *pq)
{
  return pq -> no_of_elements == 0;
}

// Use this when you want to make an array as a whole as the priority queue
BinaryHeap_pq* make_pq(int x, long long *dist)
{
    BinaryHeap_pq* pq = (BinaryHeap_pq*) malloc (sizeof(BinaryHeap_pq));

    pq -> no_of_elements = 1;   // because only source is 0 and is only in the queue
    // pq -> size = x;

    pq -> queue = (Node_dist*) malloc(x * sizeof(Node_dist));
    Node_dist temp;
    int i;

    for (i = 0; i < x; i++)
    {
        temp.v = i;
        temp.dist = dist[i];
        pq -> queue[i]= temp;
    }

    pq -> positions = (int*) malloc(x * sizeof(int));
    for (i = 0; i < x; i++)
        pq -> positions[i] = i;
    
    build_minheap(pq);
}

// int main()
// {
//     return 0;
// }
