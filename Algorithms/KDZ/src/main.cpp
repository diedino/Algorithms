#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <chrono>
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
void start(string path);
void writeToFile();

std::ofstream out;

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
    // запуск программы из файла
    // start(file path);
    for (int i=0; i<10; i++)
    {
        out.open("../results/results610/results610_"+to_string(i) +".txt");
        start("../input/input_610_0.0.txt");
        start("../input/input_610_0.5.txt");
        start("../input/input_610_1.0.txt");
        start("../input/input_610_disco.txt");
        out.close();
    }
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

void start(string path) {
    cout << "---------------------------" << endl;
    cout << path << endl;
    if (out.is_open())
    {
        out<<path<<endl;
    }
    vector<vector<int>> graph = readMatrix(path);
    cout << graph.size()<< " "<< graph[0].size()<<endl;
    vector<pair<int,int>> allPairs = findAllPairs(graph);
    Ford_Fulkerson fordFulkerson = Ford_Fulkerson(graph, allPairs);
    Edmond_Karp edmondKarp = Edmond_Karp(graph, allPairs);
    Dinic dinic = Dinic(graph, graph.size(), allPairs);
    auto start = std::chrono::high_resolution_clock::now();
    fordFulkerson.runAlgorithm();
    auto finish = std::chrono::high_resolution_clock::now();
    if (out.is_open())
    {
        out<<"Ford-Fulkerson time: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n" <<endl;
    }
    cout<<"Ford-Fulkerson time: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n" <<endl;
    start = std::chrono::high_resolution_clock::now();
    edmondKarp.runAlgorithm();
    finish = std::chrono::high_resolution_clock::now();
    if (out.is_open())
    {
        out<<"Edmond-Karp time: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n" <<endl;
    }
    cout<<"Edmond-Karp time: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n" <<endl;
    start = std::chrono::high_resolution_clock::now();
    dinic.runAlgorithm();
    finish = std::chrono::high_resolution_clock::now();
    if (out.is_open())
    {
        out<<"Dinic time: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n"<< endl;
        out << "---------------------------"<<endl;
    }
    cout<<"Dinic time: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n"<< endl;
    cout <<"---------------------------"<<endl;
}
