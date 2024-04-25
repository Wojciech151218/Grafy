//
// Created by wojciech on 24.04.24.
//

#ifndef UNTITLED16_ADJACENCYLISTGRAPH_H
#define UNTITLED16_ADJACENCYLISTGRAPH_H
#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include "memory"

class AdjacencyListGraph {


public:
    explicit AdjacencyListGraph(const std::vector<std::vector<int>> &adjacencyVector);
    void DFS(int vertex = {0} ,std::unordered_set<int> * traversed = nullptr);
    void BFS();

private:
    std::map<int, std::vector<int>> adjacencyList;


};


#endif //UNTITLED16_ADJACENCYLISTGRAPH_H
