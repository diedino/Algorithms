#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include "algorithm"
#include "vector"
#include "limits.h"
#include <queue>
#include <ctime>
#include "Ford_Fulkerson/Ford_Fulkerson.h"
#include "Edmond_Carp/Edmond_Karp.h"
#include "Dinic/Dinic.h"

using namespace std;

int dfs(vector<vector<int>>& graph, int index);
vector<std::pair<int, int>> findAllPairs(vector<vector<int>>& graph);
bool isSource(vector<vector<int>>& graph, int index);
bool isTarget(vector<vector<int>>& graph, int index);
vector<vector<int>> readMatrix(string filename);

//**********************
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
//**********************

vector<vector<int>> readMatrix(string filename);

int main() {
    vector<vector<int>> graph = readMatrix("../input/input_910_0.0.txt");
    cout << graph.size()<< " "<< graph[0].size()<<endl;
    vector<pair<int,int>> allPairs = findAllPairs(graph);
    Ford_Fulkerson fordFulkerson = Ford_Fulkerson(graph, allPairs);
    Edmond_Karp edmondKarp = Edmond_Karp(graph, allPairs);
    Dinic dinic = Dinic(graph, graph.size(), allPairs);
    clock_t start=clock();
    fordFulkerson.runAlgorithm();
    clock_t end=clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    cout<<"Ford-Fulkerson time: "<<time<<endl;
    start = clock();
    edmondKarp.runAlgorithm();
    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
    cout<<"Edmond-Karp time: "<<time<<endl;
    start = clock();
    dinic.runAlgorithm();
    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
    cout<<"Dinic time: "<<time<<endl;
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