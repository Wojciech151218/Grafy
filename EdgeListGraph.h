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

class EdgeListGraph {
public:
    struct Edge {
        int sourceVertex;
        int destinationVertex;

        Edge(int dest, int src ) : sourceVertex(src), destinationVertex(dest) {};
    };
    EdgeListGraph(std::vector<Edge> edgeList);
    void DFS(int vertex = 0 ,std::unordered_set<int> * traversed = nullptr);
    void BFS(int vertex = 0 ,std::unordered_set<int> * traversed = nullptr);
    void addEdge(Edge edge);
private:
    std::vector<Edge> edges;

};


#endif //UNTITLED16_EDGELISTGRAPH_H
