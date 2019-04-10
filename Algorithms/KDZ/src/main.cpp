#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include "algorithm"
#include "vector"
#include "limits.h"
#include <queue>
#include "Ford_Fulkerson/Ford_Fulkerson.h"
#include "Edmond_Carp/Edmond_Karp.h"
#include "Dinic/Dinic.h"

using namespace std;

//**********************
bool isSource(vector<vector<int>>& graph, int index)
{
    for (int i = 0; i < graph.size(); i++)
        if (graph[i][index] != 0)
            return false;
    return true;
}

bool isTarget(vector<vector<int>>& graph, int index)
{
    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[index][i] != 0)
            return false;
    }
    return true;
}

int dfs(vector<vector<int>>& graph, int index)
{
    bool visited[graph.size()];
    memset(visited, 0, sizeof(visited));
    queue<int> q;
    q.push(index);
    visited[index] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < graph.size(); v++)
        {
            if (!visited[v] && graph[u][v] != 0)
            {
                q.push(v);
                visited[v] = true;
                if (isTarget(graph, v))
                    return v;
            }
        }
    }
}

vector<std::pair<int, int>> findAllPairs(vector<vector<int>>& graph)
{
    vector<pair<int, int>> result;
    for (int i = 0; i < graph.size(); i++)
        if (isSource(graph, i))
            result.push_back(make_pair(i, dfs(graph, i)));
    return result;
}
//**********************

vector<vector<int>> readMatrix(string filename);

int main() {
    vector<vector<int>> graph = readMatrix("../input/input_10_disco.txt");
    for(int i=0;i<graph[0].size(); i++){
        for(int j=0;j<graph[0].size();j++)
            printf("%d\t",graph[i][j]);
        printf("\n");
    }
    cout << graph.size()<< " "<< graph[0].size()<<endl;
    vector<pair<int,int>> allPairs = findAllPairs(graph);
    Ford_Fulkerson fordFulkerson = Ford_Fulkerson(graph, allPairs);
    Edmond_Karp edmondKarp = Edmond_Karp(graph, allPairs);
    Dinic dinic = Dinic(graph.size(), allPairs);
    dinic.readFromMatrix(graph);
    fordFulkerson.runAlgorithm();
    edmondKarp.runAlgorithm();
    dinic.runAlgorithm();
    return 0;
}

vector<vector<int>> readMatrix(string filename)
{
    ifstream fin;
    fin.open(filename);
    string row;
    vector<vector<int>> result;
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            vector<int> arr;
            getline(fin, row);
            stringstream stream(row);
            int n;
            while (stream >> n)
                arr.push_back(n);
            if (!arr.empty())
                result.push_back(arr);
        }
    }
    else
    {
        cout << "File broken!";
        exit(1);
    }
    return result;
}