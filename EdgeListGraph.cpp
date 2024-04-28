

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
    std::unordered_set<int> visited;// kontener dla już odwiedzonych wierzchołków
    std::queue<int> queue;// kolejka w której zapisujemy wierzchołki do odwiedzenia w kolejnych iteracjach algorytmu

    queue.push(vertex);
    visited.insert(vertex);

    while (not queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();
        std::cout << currentVertex << " ";

        // Przechodzimy przez wszystkie krawędzie
        for (Edge edge : edges) {
            // Jeśli krawędź zaczyna się w obecnym wierzchołku i jej koniec nie był odwiedzony, dodajemy go do kolejki
            if (edge.sourceVertex == currentVertex and
                visited.find(edge.destinationVertex) == visited.end()) {
                queue.push(edge.destinationVertex);
                visited.insert(edge.destinationVertex);
            }
        }
    }
}

void EdgeListGraph::topologicalSortBFS() {
    // Obliczamy stopień wejściowy dla każdego wierzchołka
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

    // kolejkujemy wierzchołki o stopniu równym 0
    for (int i = 0; i < indegree.size(); ++i) {
        if (indegree[i] == 0)
            q.push(i);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        result.push_back(v);

        //
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

void EdgeListGraph::DFSUtil(int vertex, std::map<int,Colour> * colours, std::stack<int>& stack) {
    (*colours)[vertex] = Grey;

    // Przechodzimy przez wszystkie krawędzie
    for (auto &&edge : edges) {
        if (edge.sourceVertex==vertex and
            (*colours)[edge.destinationVertex]==White)
            DFSUtil(edge.destinationVertex, colours, stack);
    }
    (*colours)[vertex] = Black;
    stack.push(vertex);
}

void EdgeListGraph::topologicalSortDFS() {
    std::stack<int> stack;
    std::map<int,Colour> colours;

    // Inicjujemy mapę kolorów dla wierzchołków
    for(auto&& edge : edges){
        auto destination = colours.find(edge.destinationVertex);
        auto source = colours.find(edge.sourceVertex);
        if(source == colours.end())
            colours.emplace(edge.sourceVertex,White);
        if(destination == colours.end())
            colours.emplace(edge.destinationVertex,White);
    }

    // Przechodzimy przez wszystkie krawędzie
    for (const auto& edge : edges) {
        int vertex = edge.sourceVertex;
        // Jeśli wierzchołek jest biały, rozpoczynamy od niego DFS
        if (colours[vertex]==White)
            DFSUtil(vertex, &colours, stack);
    }

    // Wyświetlamy topologiczne uporządkowanie
    while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
}
