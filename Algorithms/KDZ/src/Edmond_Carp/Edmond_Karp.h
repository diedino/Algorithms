//
// Created by krasn on 02.04.2019.
//

#ifndef WORK_EDMONDKARP_H
#define WORK_EDMONDKARP_H
#include <vector>


using namespace std;
class Edmond_Karp
{
public:
    Edmond_Karp(vector<vector<int>> vector1, vector<pair<int, int>> pairs);
    void runAlgorithm();
    int edmondKarp(vector<vector<int>>& G,int s,int t);

private:
    vector<vector<int>> graph;
    vector<std::pair<int, int>> allPairs;
};


#endif //KDZ_H
