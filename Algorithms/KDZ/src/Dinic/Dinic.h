//
// Created by krasn on 09.04.2019.
//

#ifndef MODULEHOMETASK_DINIC_H
#define MODULEHOMETASK_DINIC_H

#include <vector>

using namespace std;

struct Edge
{
    int v ;
    int flow ;
    int C;
    int rev ;
};

class Dinic
{
private:
    int V; // вершины
    int *level ; // уровень в ноде
    vector<Edge> *adj;
    vector<std::pair<int, int>> allPairs;
public:
    Dinic(vector<vector<int>> matrix, int V, vector<std::pair<int, int>> pairs);
    void runAlgorithm();
    void readFromMatrix(vector<vector<int>> matrix);
    void addEdge(int u, int v, int C);
    bool BFS(int s, int t);
    int dfs(int s, int flow, int t, int ptr[]);
    int dinicMaxflow(int s, int t);
};


#endif //KDZ_DINIC_H
