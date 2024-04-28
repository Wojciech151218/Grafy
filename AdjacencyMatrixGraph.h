//
// Created by wojciech on 28.04.24.
//

#ifndef UNTITLED16_ADJACENCYMATRIXGRAPH_H
#define UNTITLED16_ADJACENCYMATRIXGRAPH_H
#include "IGraph.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <memory>
#include <queue>
#include "library.h"
#include <stack>

class AdjacencyMatrixGraph : private IGraph {
public:
    explicit AdjacencyMatrixGraph(const std::vector<std::vector<bool>> upperMatrix);




public:
    void DFSWithTimer(){TimeCounter timeCounter();DFS();};
    void DFS(int vertex = {0} ,std::unordered_set<int> * traversed = nullptr);
    void BFS(int vertex = 0);
    void topologicalSortBFS();
    void topologicalSortDFS();




private:
    void DFSUtil(int vertex, std::vector<Colour> * , std::stack<int> & stack);
    std::vector<std::vector<bool>> adjacencyMatrix;
};


#endif //UNTITLED16_ADJACENCYMATRIXGRAPH_H
