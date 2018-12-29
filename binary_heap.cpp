#include <algorithm>

using std::pair;

class BinaryHeap_pq
{
  public:
    int size;
    int no_of_elements;
    pair<int, long long> *queue;
    int *positions;     // Keeps track of the positions of the nodes in the queue.
  
  public:
    BinaryHeap_pq(int, long long*);
    int parent(int);
    int left(int);
    int right(int);
    void swap(int, int);
    void min_heapify(int);
    void build_minheap();
    void deleteNode(int);
    int extractMin();
    void min_upheap(int);
    void changePriority(int, int);
    bool isEmpty();
};

BinaryHeap_pq :: BinaryHeap_pq(int x, long long *dist)
{
  no_of_elements = 1;   // because only source is 0 and is only in the queue
  size = x;
  pair<int, long long> ar[size];
  size_t i;

  for (i = 0; i < size; i++)
    ar[i] = pair<int, long long> (i, dist[i]);
  queue = ar;

  int pos[size];
  for (i = 0; i < size; i++)
    pos[i] = i;
  positions = pos;

  build_minheap();
}

int BinaryHeap_pq :: parent(int p)
{
  return (p - 1) / 2;
}

int BinaryHeap_pq :: left(int p)
{
  return p*2 + 1;
}

int BinaryHeap_pq :: right(int p)
{
  return p*2 + 2;
}

void BinaryHeap_pq :: swap(int x, int y)
{
  int pos1 = queue[x].first, pos2 = queue[y].first;
  pair<int, int> temp = queue[x];
  queue[x] = queue[y];
  queue[y] = temp;

  // Changing the positions in the position array
  positions[pos1] = y;
  positions[pos2] = x;
}

void BinaryHeap_pq :: min_heapify(int node)
{
  int l, r, smallest;

  l = left(node);
  r = right(node);
  smallest = node;

  if (l < size && queue[l].second < queue[smallest].second)
    smallest = l;
  if (r < size && queue[r].second < queue[smallest].second)
    smallest = r;

  if (smallest != node)
  {
    swap(node, smallest);
    min_heapify(smallest);
  }
}

void BinaryHeap_pq :: build_minheap()
{
  for (int i = size/2; i >=0; i--)
    min_heapify(i);
}

void BinaryHeap_pq :: deleteNode(int pos)
{
    swap(pos, size - 1);
    size--;
    min_heapify(pos);
    no_of_elements--;
}

// Returns the node with lowest dist value
int BinaryHeap_pq :: extractMin()
{
    int node = queue[0].first;
    deleteNode(0);
    return node;
}

void BinaryHeap_pq :: min_upheap(int node)
{
  int par = parent(node);

  if (par >= 0 &&  queue[node].second < queue[par].second)
  {
    swap(node, par);
    min_upheap(par);
  }
}

void BinaryHeap_pq :: changePriority(int node, int val)
{
  int pos = positions[node];
  queue[pos].second = val;    // The value at pos can only be decreased
  min_upheap(pos);
  no_of_elements++;
}

bool BinaryHeap_pq :: isEmpty()
{
  return no_of_elements == 0;
}

int main() 
{
  return 0;
}
