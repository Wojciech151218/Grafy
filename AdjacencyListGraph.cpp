//
// Created by wojciech on 24.04.24.
//

#include "AdjacencyListGraph.h"


AdjacencyListGraph::AdjacencyListGraph(const std::vector<std::vector<bool>> upperMatrix) {
    for (int i = 0; i < upperMatrix.size(); ++i){
        std::vector<int> temp;
        for(int j = 0; j < upperMatrix.size()-i; ++j)
            if(upperMatrix[i][j]) temp.push_back(j+i+1);
        adjacencyList.emplace(i,temp);
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
        if (traversed->find(neighbour) == traversed->end())
            DFS(neighbour, traversed);
    }

    return;
}

void AdjacencyListGraph::BFS(int vertex) {
    //COUNTER
    TimeCounter timeCounter(cellInfo);
        std::unordered_set<int> visited;
        std::queue<int> queue;

        queue.push(vertex);
        visited.insert(vertex);

        while (not queue.empty()) {
            int currentVertex = queue.front();
            queue.pop();
            std::cout << currentVertex << " ";

            for (int neighbor : adjacencyList[currentVertex]) {
                if (visited.find(neighbor) == visited.end()) {
                    queue.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }
}

void AdjacencyListGraph::updateCellInfo(TimeCounter::CellInfo CI) {
    AdjacencyListGraph::cellInfo = CI;
}
void AdjacencyListGraph::topologicalSortBFS() {
    // Calculate indegrees for each vertex
    std::vector<int> indegree(adjacencyList.size(), 0);
    for (const auto& pair : adjacencyList) {
        for (int v : pair.second)
            indegree[v]++;
    }

    std::queue<int> q;
    std::vector<int> result;

    // Enqueue vertices with indegree 0
    for (int i = 0; i < indegree.size(); ++i)
        if (not indegree[i]) q.push(i);


    while (!q.empty()) {
        int v = q.front();
        q.pop();
        result.push_back(v);

        // Decrease indegree of adjacent vertices
        for (int u : adjacencyList[v]) {
            indegree[u]--;
            if (indegree[u] == 0)
                q.push(u);
        }
    }

    // Output topological order
    for (int v : result)
        std::cout << v << " ";


}

void AdjacencyListGraph::DFSUtil(int vertex, std::vector<Colour> * colours, std::stack<int>& stack) {
    (*colours)[vertex] = Grey;

    for (int neighbour : adjacencyList[vertex]) {
        if ( (*colours)[neighbour]==White ) {
            DFSUtil(neighbour, colours, stack);
        }
    }

    (*colours)[vertex] = Black;
    stack.push(vertex);
}

void AdjacencyListGraph::topologicalSortDFS() {
    std::stack<int> stack;
    std::vector<Colour> colours(adjacencyList.size(),White);

    for (const auto& pair : adjacencyList) {
        int vertex = pair.first;
        if (colours[vertex] == White) {
            DFSUtil(vertex, &colours, stack);
        }
    }

    // Print the topological ordering
    while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
}