//
// Created by krasn on 08.04.2019.
//

#ifndef MODULEHOMETASK_FORD_FULKERSON_H
#define MODULEHOMETASK_FORD_FULKERSON_H

#include<vector>

using namespace std;

class Ford_Fulkerson
{
public:
    Ford_Fulkerson();
    int fordFulkerson(vector<vector<int> >&graph, int s, int t , int V);
    int vertex;
private:
    bool bfs(vector<vector<int> >&rGraph, int s, int t, int parent[] , int V);

};


#endif //MODULEHOMETASK_FORD_FULKERSON_H
