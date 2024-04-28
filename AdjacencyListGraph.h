//
// Created by wojciech on 24.04.24.
//

#ifndef UNTITLED16_ADJACENCYLISTGRAPH_H
#define UNTITLED16_ADJACENCYLISTGRAPH_H
#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <memory>
#include <queue>
#include "library.h"
#include <stack>

class AdjacencyListGraph {
private:
    enum Colour{White,Grey,Black};


public:
    explicit AdjacencyListGraph(const std::vector<std::vector<bool>> upperMatrix);
    void DFS(int vertex = {0} ,std::unordered_set<int> * traversed = nullptr);
    void DFSWithTimer(){ TimeCounter timeCounter(cellInfo);DFS();}
    void BFS(int vertex = 0);
    void topologicalSortBFS();
    void topologicalSortDFS();
    void DFSUtil(int vertex, std::vector<Colour> * , std::stack<int> & stack);


    static void updateCellInfo(TimeCounter::CellInfo);

private:
    static inline TimeCounter::CellInfo cellInfo;
    std::map<int, std::vector<int>> adjacencyList;


};


#endif //UNTITLED16_ADJACENCYLISTGRAPH_H
