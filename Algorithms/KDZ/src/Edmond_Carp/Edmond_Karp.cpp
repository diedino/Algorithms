//
// Created by krasn on 02.04.2019.
//

#include <queue>
#include <iostream>
#include "Edmond_Karp.h"

const int INF = 1000 * 1000 * 1000;

bool bfs(vector<vector<int>>& residualGraph, int s, int t, vector<int>& parent);


int Edmond_Karp::edmondKarp(vector<vector<int>> &G, int s, int t){
    vector<vector<int>> residualGraph;
    copy(G.begin(), G.end(), back_inserter(residualGraph));
    vector<int> parent(G.size());
    int maxflow = 0;
    int v, u;
    while (bfs(residualGraph, s, t, parent))
    {

        int pathFlow = INF;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }
        maxflow += pathFlow;

    }
    return maxflow;

}

Edmond_Karp::Edmond_Karp(vector<vector<int>> vector1, vector<pair<int, int>> pairs)
{
    graph = vector1;
    allPairs = pairs;
}

void Edmond_Karp::runAlgorithm()
{
    for(int i=0; i<allPairs.size(); ++i) {
        int res = edmondKarp(graph, allPairs[i].first, allPairs[i].second);
        cout << res << endl;
    }
}

bool bfs(vector<vector<int>>& residualGraph, int s, int t, vector<int>& parent) {
    int amount = parent.size();
    vector<bool> visited(amount, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (q.size() != 0)
    {
        if (visited[t])
            break;

        int u = q.front();
        q.pop();

        for (int v = 0; v < amount; ++v)
        {
            if (visited[v] || residualGraph[u][v] <= 0)
                continue;
            q.push(v);
            parent[v] = u;
            visited[v] = true;
        }
    }

    return visited[t];
}
