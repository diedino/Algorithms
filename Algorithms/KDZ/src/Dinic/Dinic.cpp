//
// Created by krasn on 09.04.2019.
//

#include <list>
#include <limits.h>
#include <iostream>
#include "Dinic.h"


Dinic::Dinic(vector<vector<int>> matrix, int V, vector<std::pair<int, int>> pairs)
{
    adj = new vector<Edge>[V];
    this->V = V;
    level = new int[V];
    readFromMatrix(matrix);
    allPairs = pairs;
}

void Dinic::addEdge(int u, int v, int C)
{
    // Forward edge : 0 flow and C capacity
    Edge a{v, 0, C, (int)adj[v].size()};

    // Back edge : 0 flow and 0 capacity
    Edge b{u, 0, 0, (int)adj[u].size()};

    adj[u].push_back(a);
    adj[v].push_back(b); // reverse edge
}

bool Dinic::BFS(int s, int t)
{
    for (int i = 0 ; i < V ; i++)
        level[i] = -1;

    level[s] = 0;  // Level of source vertex

    // Create a queue, enqueue source vertex
    // and mark source vertex as visited here
    // level[] array works as visited array also.
    list<int> q;
    q.push_back(s);

    vector<Edge>::iterator i ;
    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();
        for (i = adj[u].begin(); i != adj[u].end(); i++)
        {
            Edge &e = *i;
            if (level[e.v] < 0  && e.flow < e.C)
            {
                // Level of current vertex is,
                // level of parent + 1
                level[e.v] = level[u] + 1;

                q.push_back(e.v);
            }
        }
    }

    // IF we can not reach to the sink we
    // return false else true
    return level[t] >= 0;
}

int Dinic::dfs(int u, int flow, int t, int start[])
{
    // Sink reached
    if (u == t)
        return flow;

    // Traverse all adjacent edges one -by - one.
    for (  ; start[u] < adj[u].size(); start[u]++)
    {
        // Pick next edge from adjacency list of u
        Edge &e = adj[u][start[u]];

        if (level[e.v] == level[u]+1 && e.flow < e.C)
        {
            // find minimum flow from u to t
            int curr_flow = min(flow, e.C - e.flow);

            int temp_flow = dfs(e.v, curr_flow, t, start);

            // flow is greater than zero
            if (temp_flow > 0)
            {
                // add flow  to current edge
                e.flow += temp_flow;

                // subtract flow from reverse edge
                // of current edge
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }

    return 0;
}

int Dinic::dinicMaxflow(int s, int t)
{
    // Corner case
    if (s == t)
        return -1;

    int total = 0;  // Initialize result

    // Augment the flow while there is path
    // from source to sink
    while (BFS(s, t) == true)
    {
        // store how many edges are visited
        // from V { 0 to V }
        int *start = new int[V+1];

        // while flow is not zero in graph from S to D
        while (int flow = dfs(s, INT_MAX, t, start))

            // Add path flow to overall flow
            total += flow;
    }

    // return maximum flow
    return total;
}

void Dinic::readFromMatrix(vector<vector<int>> matrix)
{
    for (int i=0; i<matrix[0].size(); ++i) {
        for (int j=0; j<matrix.size(); ++j) {
            if (matrix[i][j] !=0) {
                addEdge(i, j, matrix[i][j]);
            }
        }
    }
}

void Dinic::runAlgorithm()
{
    for(int i=0; i<allPairs.size(); ++i) {
        int res = dinicMaxflow(allPairs[i].first, allPairs[i].second);
        cout << res << endl;
    }
}
