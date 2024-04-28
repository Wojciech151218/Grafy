

//
// Created by wojciech on 08.04.24.
//

#include "EdgeListGraph.h"

void EdgeListGraph::addEdge(EdgeListGraph::Edge edge) {
    edges.push_back(edge);
}


EdgeListGraph::EdgeListGraph(std::vector<std::vector<bool>> upperMatrix){
    for (int i = 0; i < upperMatrix.size(); ++i){
        for(int j = 0; j < upperMatrix.size()-i; ++j)
            if(upperMatrix[i][j]) edges.push_back({j+i+1,i});
    }
}




void EdgeListGraph::DFS(int vertex, std::unordered_set<int> * traversed) {
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

void EdgeListGraph::BFS(int vertex) {
    std::unordered_set<int> visited;
    std::queue<int> queue;

    queue.push(vertex);
    visited.insert(vertex);

    while (not queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();
        std::cout << currentVertex << " ";

        for (Edge edge : edges) {
            if (visited.find(edge.destinationVertex) == visited.end()) {
                queue.push(edge.destinationVertex);
                visited.insert(edge.destinationVertex);
            }
        }
    }

}
void EdgeListGraph::topologicalSortBFS() {
    // Calculate indegrees for each vertex

    std::unordered_map<int,int> indegree;
    for (const auto& edge : edges) {
        auto destination = indegree.find(edge.destinationVertex);
        auto source = indegree.find(edge.sourceVertex);
        if(source == indegree.end())
            indegree.emplace(edge.sourceVertex,0);
        if(destination != indegree.end())
            indegree[edge.destinationVertex]++;
        else
            indegree.emplace(edge.destinationVertex,1);
    }

    std::queue<int> q;
    std::vector<int> result;

    // Enqueue vertices with indegree 0
    for (int i = 0; i < indegree.size(); ++i) {
        if (indegree[i] == 0)
            q.push(i);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        result.push_back(v);

        // Decrease indegree of adjacent vertices
        for (auto &&edge : edges) {
            if(edge.sourceVertex != v) continue;
            int u = edge.destinationVertex;
            indegree[u]--;
            if (not indegree[u])
                q.push(u);
        }
    }

    // Output topological order
    for (int v : result)
        std::cout << v << " ";


}

void EdgeListGraph::DFSUtil(int vertex, std::unordered_set<int>& visited, std::stack<int>& stack) {
    visited.insert(vertex);

    for (auto &&edge : edges) {
        if (edge.sourceVertex==vertex and visited.find(edge.destinationVertex) == visited.end()) {
            DFSUtil(edge.destinationVertex, visited, stack);
        }
    }

    stack.push(vertex);
}

void EdgeListGraph::topologicalSortDFS() {
    std::stack<int> stack;
    std::unordered_set<int> visited;

    for (const auto& edge : edges) {
        int vertex = edge.sourceVertex;
        if (visited.find(vertex) == visited.end())
            DFSUtil(vertex, visited, stack);
    }

    // Print the topological ordering
    while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
}
