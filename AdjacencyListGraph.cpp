//
// Created by wojciech on 24.04.24.
//

#include "AdjacencyListGraph.h"

AdjacencyListGraph::AdjacencyListGraph(const std::vector<std::vector<bool>> upperMatrix) {
    // Tworzymy listę sąsiedztwa na podstawie górnego trójkątnego macierzy
    for (int i = 0; i < upperMatrix.size(); ++i) {
        std::vector<int> temp;
        // Przechodzimy po kolumnach, zaczynając od i-tej, aby uniknąć powtórzeń
        for(int j = 0; j < upperMatrix.size()-i; ++j) {
            if (upperMatrix[i][j]) {
                // Jeśli istnieje krawędź, dodajemy wierzchołek sąsiadujący do listy
                temp.push_back(j+i+1);
            }
        }
        // Dodajemy listę sąsiedztwa dla danego wierzchołka do mapy
        adjacencyList.emplace(i,temp);
    }
}

void AdjacencyListGraph::DFS(int vertex ,std::unordered_set<int>* traversed ) {
    std::unique_ptr<std::unordered_set<int>> traversedPtr;// tworzymy kontener dla odwiedzonych wierzchołków
    if (not traversed) {
        traversedPtr = std::make_unique<std::unordered_set<int>>();
        traversed = traversedPtr.get();
    }
    traversed->insert(vertex);//dodajemy obecny wierzchołek do odwiedzonych
    std::cout << vertex << " ";
    // Przechodzimy przez sąsiadów danego wierzchołka
    for (const auto& neighbour : adjacencyList[vertex]) {
        // Jeśli sąsiad nie był odwiedzony, rekursywnie wywołujemy DFS dla sąsiednego wierzchołka
        if (traversed->find(neighbour) == traversed->end())
            DFS(neighbour, traversed);
    }

    return;
}

void AdjacencyListGraph::BFS(int vertex) {
    //COUNTER
    TimeCounter timeCounter(cellInfo);

    std::unordered_set<int> visited;// kontener dla już odwiedzonych wierzchołków
    std::queue<int> queue; // kolejka w której zapisujemy wierzchołki do odwiedzenia w kolejnych iteracjach algorytmu

    queue.push(vertex);
    visited.insert(vertex);

    while (not queue.empty()) {
        int currentVertex = queue.front();// pobieramy wierzchołek z przodu kolejki
        queue.pop();
        std::cout << currentVertex << " ";

        // Przechodzimy przez sąsiadów danego wierzchołka
        for (int neighbor : adjacencyList[currentVertex]) {
            if (visited.find(neighbor) == visited.end()) {
                queue.push(neighbor);//sąsiedzi są dodawani do kolejki oraz do odwiedzonych wierzchołków
                visited.insert(neighbor);
            }
        }
    }
}

void AdjacencyListGraph::topologicalSortBFS() {
    // Obliczamy stopień wejściowy dla każdego wierzchołka
    std::vector<int> indegree(adjacencyList.size(), 0);
    for (const auto& pair : adjacencyList) {
        for (int v : pair.second)
            indegree[v]++;
    }

    std::queue<int> q;
    std::vector<int> result;

    // Kolejkujemy wierzchołki o stopniu wejściowym równym 0
    for (int i = 0; i < indegree.size(); ++i)
        if (not indegree[i]) q.push(i);

    // Przechodzimy przez wierzchołki w kolejce
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        result.push_back(v);

        // Zmniejszamy stopień wejściowy dla sąsiednich wierzchołków wierzchołka v ponieważ uznajemy go za posortwanego
        for (int u : adjacencyList[v]) {
            indegree[u]--;
            if (indegree[u] == 0)
                q.push(u);//dodajemy sąsiadów do kolejki
        }
    }


    for (int v : result)
        std::cout << v << " ";
}

void AdjacencyListGraph::DFSUtil(int vertex, std::vector<Colour> * colours, std::stack<int>& stack) {
    (*colours)[vertex] = Grey;

    // Przechodzimy przez sąsiadów danego wierzchołka
    for (int neighbour : adjacencyList[vertex]) {
        if ((*colours)[neighbour] == White) {
            DFSUtil(neighbour, colours, stack);
        }
    }

    (*colours)[vertex] = Black;
    stack.push(vertex);
}

void AdjacencyListGraph::topologicalSortDFS() {
    std::stack<int> stack;
    std::vector<Colour> colours(adjacencyList.size(),White);

    // Przechodzimy przez wszystkie wierzchołki
    for (const auto& pair : adjacencyList) {
        int vertex = pair.first;
        // Jeśli wierzchołek jest biały, rozpoczynamy od niego DFS
        if (colours[vertex] == White) {
            DFSUtil(vertex, &colours, stack);
        }
    }

    while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
}
