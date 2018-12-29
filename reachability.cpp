#include <iostream>
#include <vector>

using namespace std;

vector<int> dfs(vector<vector<int> > &adj, vector<bool> &visited, vector<vector<bool> > &reachable, int s)
{
    int v;
    size_t i;
    visited[s] = true;
    vector<int> reach, temp;
    reach.push_back(s);

    for (i = 0; i < adj[s].size(); i++)
    {
        v = adj[s][i];
        if (!visited[v])
        {
            temp = dfs(adj, visited, reachable, v);
            reach.insert(reach.end(), temp.begin(), temp.end());
        }
        else
            reach.insert(reach.end(), reachable[v].begin(), reachable[v].end());
    }
    
    for (i = 0; i < reach.size(); i++)
    {
        v = reach[i];
        reachable[s][v] = true;
    }

    return reach;
}

void show(vector<vector<bool> > &reachable)
{
    for (size_t i = 0; i < reachable.size(); i++)
    {
        cout << i + 1 << ": ";
        for (size_t j = 0; j < reachable[i].size(); j++)
        {
            if (reachable[i][j])
            cout << j + 1 << " ";
        }
        cout << endl;
    }
}

void reachability(vector<vector<int> > &adj)
{
    int size = adj.size();
    size_t i;
    vector<bool> visited(size, false);
    vector<vector<bool> > reachable(size, vector<bool>(size, false));

    for (i = 0; i < size; i++)
        if (!visited[i])
            dfs(adj, visited, reachable, i);
    
    show(reachable);
}


int main()
{
    int n, m, x, y;
    size_t i;

    cin >> n >> m;
    vector<vector<int> >adj(n, vector<int>());

    for (i = 0; i < m; i++)
    {
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    reachability(adj);

    return 0;
}
