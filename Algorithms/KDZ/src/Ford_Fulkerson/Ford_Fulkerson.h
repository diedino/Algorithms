//
// Created by krasn on 10.04.2019.
//

#ifndef KDZ_FORD_FULKERSON_H
#define KDZ_FORD_FULKERSON_H

#include <vector>

using namespace std;

class Ford_Fulkerson
{
public:
    Ford_Fulkerson(vector<vector<int>> vector1, vector<pair<int, int>> pairs);
    void runAlgorithm();
    int fordFulkerson(vector<vector<int>>& G, int s, int t);
private:
    vector<vector<int>> graph;
    vector<std::pair<int, int>> allPairs;
    int findPath(vector<vector<int>>& G, vector<bool>& visitedArr, int u, int t, int f);
};


#endif //KDZ_FORD_FULKERSON_H
