#include <iostream>

using namespace std;

struct node
{
    int data, degree;
    struct node *parent, *sibling, *child;
};
typedef struct node Node;

Node* makeHeap(int x)
{
    Node *n = new Node;
    n -> data = x;
    n -> degree = 0;
    n -> parent = n -> sibling = n -> child = NULL:

    return n;
}

Node 


int main()
{
    
    return 0;
}