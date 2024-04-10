#include <iostream>
#include "Graph.h"
#include "Graph.cpp"
#include <random>

#include <vector>
int getRandomInteger(int a, int b){
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the random number generator

    // Define a distribution to generate numbers between 1 and b
    std::uniform_int_distribution<> dis(a, b);

    // Generate and return a random number
    return dis(gen);
}
int main() {
    std::vector<Graph<int>::Edge> edgeList = {Graph<int>::Edge(0,1),
                                              Graph<int>::Edge(2,1),
                                              Graph<int>::Edge(3,1),
                                              Graph<int>::Edge(4,1),
                                              Graph<int>::Edge(5,1),

                                              };
    Graph<int> graph(edgeList);
    std::vector<Graph<int>::Edge> edgeList1;
    for (int i = 0; i < 10; ++i) {
        Graph<int>::Edge  edge = {getRandomInteger(0,3), getRandomInteger(0,3)};
        edgeList1.push_back(edge);
    }

    Graph<int> graph1(edgeList1);
    graph.DFS(1);
    //graph.DFS(0);
    //graph1.DFS(2);
    return 0;
}
