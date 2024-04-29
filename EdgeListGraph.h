//
// Created by wojciech on 08.04.24.
//
//tabele krawedzi
//DFS
#ifndef UNTITLED16_EDGELISTGRAPH_H
#define UNTITLED16_EDGELISTGRAPH_H
#include <vector>
#include <iostream>
#include <unordered_set>
#include <memory>
#include <queue>
#include <stack>
#include "library.h"
#include "IGraph.h"

class EdgeListGraph : public IGraph{
public:
    struct Edge {
        int sourceVertex;
        int destinationVertex;

        Edge(int dest, int src ) : sourceVertex(src), destinationVertex(dest) {};
    };
    EdgeListGraph(std::vector<std::vector<bool>> upperMatrix);
    void DFS(int vertex = 0 ,std::unordered_set<int> * traversed = nullptr);
    void BFS(int vertex = 0);
    void topologicalSortBFS();
    void topologicalSortDFS();
    void DFSWithTimer(){ TimeCounter timeCounter(cellInfo);DFS();}
    void static updateCellInfo(TimeCounter::CellInfo CI){cellInfo = CI;};

private:
    void DFSUtil(int vertex, std::map<int,Colour> *, std::stack<int> & stack);
    std::vector<Edge> edges;



};


#endif //UNTITLED16_EDGELISTGRAPH_H
