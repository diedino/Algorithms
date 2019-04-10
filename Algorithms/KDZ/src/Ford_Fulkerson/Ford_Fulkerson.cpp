//
// Created by krasn on 10.04.2019.
//

#include <limits.h>
#include <cstring>
#include <queue>
#include <iostream>
#include <vector>
#include "Ford_Fulkerson.h"

using namespace std;

int Ford_Fulkerson::fordFulkerson(vector<vector<int>> &G, int s, int t)
{
    for (int flow = 0;;)
    {
        vector<bool> visitedArr(G.size(), false);
        int df = findPath(G,visitedArr,s,t,INT_MAX);
        if (df == 0)
            return flow;
        flow += df;
    }
}

int Ford_Fulkerson::findPath(vector<vector<int>> &G, vector<bool> &visitedArr, int u, int t, int f)
{
    if (u == t)
        return f;
    visitedArr[u] = true;
    for (int v = 0; v < visitedArr.size(); v++)
        if (!visitedArr[v] && G[u][v] > 0) {
            int df = findPath(G, visitedArr, v, t, min(f, G[u][v]));
            if (df > 0) {
                G[u][v] -= df;
                G[v][u] += df;
                return df;
            }
        }
    return 0;
}

Ford_Fulkerson::Ford_Fulkerson(vector<vector<int>> vector1, vector<pair<int,int>> pairs)
{
    graph = vector1;
    allPairs = pairs;
}

void Ford_Fulkerson::runAlgorithm()
{
    for(int i=0; i<allPairs.size(); ++i) {
        int res = fordFulkerson(graph, allPairs[i].first, allPairs[i].second);
        cout << res << endl;
    }
}

