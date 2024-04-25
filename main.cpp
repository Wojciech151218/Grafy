#include <iostream>
#include "EdgeListGraph.h"
#include <random>

#include <vector>
#include "AdjacencyListGraph.h"
int getRandomInteger(int a, int b){
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the random number generator

    // Define a distribution to generate numbers between 1 and b
    std::uniform_int_distribution<> dis(a, b);

    // Generate and return a random number
    return dis(gen);
}
int main() {
    AdjacencyListGraph adjacencyListGraph({{1,2},{1,3,4},{1,2,4}});
    adjacencyListGraph.DFS();
    printf("\n");
    std::vector<EdgeListGraph::Edge> edgeList = {EdgeListGraph::Edge(0, 1),
                                                      EdgeListGraph::Edge(2, 1),
                                                      EdgeListGraph::Edge(3, 1),
                                                      EdgeListGraph::Edge(4, 1),
                                                      EdgeListGraph::Edge(5, 1),

                                              };

    EdgeListGraph graph(edgeList);
    std::vector<EdgeListGraph::Edge> edgeList1;
    for (int i = 0; i < 10; ++i) {
        EdgeListGraph::Edge  edge = {getRandomInteger(0, 3), getRandomInteger(0, 3)};
        edgeList1.push_back(edge);
    }

    EdgeListGraph graph1(edgeList1);
    //graph.DFS(1);
    //graph.DFS(0);
    graph1.DFS(2);
    return 0;
}
