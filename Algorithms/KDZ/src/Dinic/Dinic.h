//
// Created by krasn on 09.04.2019.
//

#ifndef MODULEHOMETASK_DINIC_H
#define MODULEHOMETASK_DINIC_H

#include <vector>

using namespace std;

struct Edge
{
    int v ;  // Vertex v (or "to" vertex)
    // of a directed edge u-v. "From"
    // vertex u can be obtained using
    // index in adjacent array.

    int flow ; // flow of data in edge
    int C;    // capacity
    int rev ; // To store index of reverse
    // edge in adjacency list so that
    // we can quickly find it.
};

class Dinic
{
private:
    int V; // number of vertex
    int *level ; // stores level of a node
    vector<Edge> *adj;
    vector<std::pair<int, int>> allPairs;
public:
    Dinic(int V, vector<std::pair<int, int>> pairs);
    void runAlgorithm();
    void readFromMatrix(vector<vector<int>> matrix);
    void addEdge(int u, int v, int C);
    bool BFS(int s, int t);
    int dfs(int s, int flow, int t, int ptr[]);
    int dinicMaxflow(int s, int t);
};


#endif //KDZ_DINIC_H
