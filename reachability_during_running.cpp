#include <iostream>
#include <vector>

using namespace std;

/*
    @param marked - keeps a record of the vertices which can reach t and have already been marked
    @param path - stores the vertices that are in the current path in order to detect cycles
    @param toBeEntered - stores the vertices which can reach t and have not been marked.
*/
// void explore(vector<vector <int> > &adj, vector<vector <int> > &reachable, vector<bool> &visited, vector<bool> &path, vector<bool> &marked, vector<int> &toBeEntered, int v, int t) 
// {
//     if (v == t)
//     {
//         reachable[t].insert(reachable[t].end(), toBeEntered.begin(), toBeEntered.end());
//         for (size_t i = 0; i < toBeEntered.size(); i++)
//             marked[toBeEntered[i]] = true;

//         toBeEntered.clear();
//         return;
//     }

//     // For detecting cycles
//     // if(path[v])
//     //     return;

//     // If not already marked and is not in current path i.e does not form a cycle
//     if (!marked[v] && !path[v])
//         toBeEntered.push_back(v);
  
//     visited[v] = true;
//     path[v] = true;
//     int u;
//     for (size_t i = 0; i < adj[v].size(); i++) 
//     {
//         u = adj[v][i];

//         if (!marked[v] && marked[u])
//         {
//             reachable[t].insert(reachable[t].end(), toBeEntered.begin(), toBeEntered.end());
//             marked[v] = true;
//             toBeEntered.pop_back();
//         }

//     if (!visited[u])
//         explore(adj, reachable, visited, path, marked, toBeEntered, u, t);
//     }

//     if (toBeEntered.size() > 0)
//         toBeEntered.pop_back();
//     path[v] = false;          // when the vertex has no neighbors left to be evaluated remove from path
// }


// void reachability(vector<vector<int> >& adj, vector<vector<int> >& reachable, int t)
// {
//     int size = adj.size(), i;
//     vector<bool> visited(size, false), path(size, false), marked(size, false);
//     vector<int> toBeEntered;

//     for (i = 0; i < size; i++)
//         if (!visited[i])
//             explore(adj, reachable, visited, path, marked, toBeEntered, i, t);
    
//     for (i = 0; i < reachable[t].size(); i++)
//         cout << reachable[t][i] + 1 << " ";
//     cout << endl;
// }


void explore(vector<vector<int> >& adjReverse, vector<bool> &visited, vector<vector<int> >& reachable, int v, int t)
{
    visited[v] = true;
    reachable[t].push_back(v);

    int u;
    for (size_t i = 0; i < adjReverse[v].size(); i++)
    {
        u = adjReverse[v][i];
        if (!visited[u])
            explore(adjReverse, visited, reachable, u, t);
    }
}


int main()
{
    int n, m, x, y, s, t;
    size_t i;

    cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>()), adjReverse(n, vector<int>());

    for (i = 0; i < m; i++)
    {
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adjReverse[y-1].push_back(x - 1);
    }
    cin >> s >> t;
    s--;
    t--;

    vector<vector<int> >reachable(n, vector<int>());
    // reachability(adj, reachable, t);

    
    vector<bool> visited(n, false);
    explore(adjReverse, visited, reachable, t, t);

    for (i = 0; i < reachable[t].size(); i++)
        cout << reachable[t][i] + 1 << " ";
    cout << endl;

    return 0;
}
