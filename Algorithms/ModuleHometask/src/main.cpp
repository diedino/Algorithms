#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include<vector>
#include "Ford-Fulkerson/Ford_Fulkerson.h"

using namespace std;

int main()
{
    vector<vector<int>> graph = { {0, 16, 13, 0, 0, 0},
                                 {0, 0, 10, 12, 0, 0},
                                 {0, 4, 0, 0, 14, 0},
                                 {0, 0, 9, 0, 0, 20},
                                 {0, 0, 0, 7, 0, 4},
                                 {0, 0, 0, 0, 0, 0}
    };
    Ford_Fulkerson ford_fulkerson;
    cout << ford_fulkerson.fordFulkerson(graph, 0, 5 , graph[0].size())<<endl;
    return 0;
}