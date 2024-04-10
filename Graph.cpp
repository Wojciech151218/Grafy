

//
// Created by wojciech on 08.04.24.
//

#include "Graph.h"
#include <unordered_set>

template<typename T>
void Graph<T>::addEdge(Graph::Edge edge) {
    edges.push_back(edge);
}

template<typename T>
Graph<T>::Graph(std::vector<Edge> edgeList){
    for(auto &&it :edgeList)
        addEdge(it);
}




template<typename T>
void Graph<T>::DFS(int vertex, std::unordered_set<int> * traversed) {
    std::unique_ptr<std::unordered_set<int>> traversedPtr;
    if (traversed == nullptr) {
        traversedPtr = std::make_unique<std::unordered_set<int>>();
        traversed = traversedPtr.get();
    }
    traversed->insert(vertex);//dodaje wierzchołek do odwiedzonych
    std::cout << vertex << " ";
    for(auto &&it : edges){//przechodzi przez wszsytkie krawędzie jeśli znajdzie taką która ma swój poczatek
        //w obecnym wierzchołku i jej koniec nie znajduję się w liście odwiedzonych wierzchołków rekursywnie wywołuje prcodurę DFS przekazując wierzchołek
        //na końcu krawędzi
        if(it.sourceVertex == vertex and traversed->find(it.destinationVertex) == traversed->end())
            DFS(it.destinationVertex, traversed);//po tym jak DFS dojdie do return wraca w to miejsce i iteruje przez kolejne elementy  czyli wraca
            // do wierzchołka z którego można wybrać inne wierzchołki
    }
    return;
}
