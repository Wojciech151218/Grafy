//
// Created by wojciech on 08.04.24.
//
//tabele krawedzi
//DFS
#ifndef UNTITLED16_GRAPH_H
#define UNTITLED16_GRAPH_H
#include <vector>
#include <iostream>
#include <unordered_set>
#include <memory>

template<typename T>
class Graph {
public:
    struct Edge {
        int sourceVertex;
        int destinationVertex;
        T label;

        Edge(int dest, int src ,const T& lbl = 1) : sourceVertex(src), destinationVertex(dest), label(lbl) {};
    };
    Graph(std::vector<Edge> edgeList);
    void DFS(int vertex = 0 ,std::unordered_set<int> * traversed = nullptr);
    void addEdge(Edge edge);
private:
    std::vector<Edge> edges;

};


#endif //UNTITLED16_GRAPH_H
