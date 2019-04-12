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
    // создаем два ребра с 0 флоу
    Edge a{v, 0, C, (int)adj[v].size()};
    Edge b{u, 0, 0, (int)adj[u].size()};

    adj[u].push_back(a);
    adj[v].push_back(b);
}

bool Dinic::BFS(int s, int t)
{
    for (int i = 0 ; i < V ; i++)
        level[i] = -1;
    level[s] = 0;
    // отмечаем  пройденные
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
                // уровень нынешней вершины
                level[e.v] = level[u] + 1; // +1 для родителя

                q.push_back(e.v);
            }
        }
    }
    // проверка дошли до стока или нет
    return level[t] >= 0;
}

int Dinic::dfs(int u, int flow, int t, int start[])
{
    if (u == t)
        return flow;
    for (  ; start[u] < adj[u].size(); start[u]++)
    {
        Edge &e = adj[u][start[u]];

        if (level[e.v] == level[u]+1 && e.flow < e.C)
        {
            int curr_flow = min(flow, e.C - e.flow);
            int temp_flow = dfs(e.v, curr_flow, t, start);
            if (temp_flow > 0)
            {
                e.flow += temp_flow;
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }

    return 0;
}

int Dinic::dinicMaxflow(int s, int t)
{
    if (s == t)
        return -1;

    int total = 0;
    while (BFS(s, t) == true)
    {
        int *start = new int[V+1];
        while (int flow = dfs(s, INT_MAX, t, start))
            total += flow;
    }
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
