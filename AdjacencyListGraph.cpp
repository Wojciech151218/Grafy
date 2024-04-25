//
// Created by wojciech on 24.04.24.
//

#include "AdjacencyListGraph.h"


AdjacencyListGraph::AdjacencyListGraph(const std::vector<std::vector<int>> &adjacencyVector) {
    int i = 0;
    for(auto &&it:adjacencyVector) {

        adjacencyList.emplace(i++,it);
    }
}


void AdjacencyListGraph::DFS(int vertex ,std::unordered_set<int>* traversed ) {
    std::unique_ptr<std::unordered_set<int>> traversedPtr;
    if (not traversed) {
        traversedPtr = std::make_unique<std::unordered_set<int>>();
        traversed = traversedPtr.get();
    }
    traversed->insert(vertex);
    std::cout << vertex << " ";
    for (const auto& neighbour : adjacencyList[vertex]) {
        if (traversed->find(neighbour) == traversed->end()) {
            DFS(neighbour, traversed);
        }
    }
    return;
}
