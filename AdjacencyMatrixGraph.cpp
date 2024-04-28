//
// Created by wojciech on 28.04.24.
//

#include "AdjacencyMatrixGraph.h"

AdjacencyMatrixGraph::AdjacencyMatrixGraph(const std::vector<std::vector<bool>> upperMatrix) {
    for (int i = 0; i < upperMatrix.size(); ++i) {
        std::vector<bool> temp( upperMatrix.size()+1, false);
        for (int j = 0; j < upperMatrix[i].size(); ++j)
            if(upperMatrix[i][j]) temp[i+j+1] = true;
        adjacencyMatrix.push_back(temp);
    }
    adjacencyMatrix.push_back(std::vector<bool>( upperMatrix.size()+1, false));
}

void AdjacencyMatrixGraph::DFS(int vertex, std::unordered_set<int> *traversed) {
    std::unique_ptr<std::unordered_set<int>> traversedPtr;
    if (not traversed) {
        traversedPtr = std::make_unique<std::unordered_set<int>>();
        traversed = traversedPtr.get();
    }//tworzymy kontener dla odwiedzony wierzchołków
    traversed->insert(vertex);//dodajemy pierwszy wierzchołek do listy odwiedzonych
    std::cout << vertex << " ";
    for (int i = 0;i < adjacencyMatrix[vertex].size();i++) {
        if (adjacencyMatrix[vertex][i] and traversed->find(i) == traversed->end() )//gdy znajdziemy wierzchołek sąsiadujący z obecnym wierzchołkiem
            DFS(i, traversed); // rekursywnie wywołujemy procedurę DFS i jako obecny wierzchołek przekazujemy znalezionego sąsiada
    }

    return;
}

void AdjacencyMatrixGraph::BFS(int vertex) {
    //COUNTER
    TimeCounter timeCounter(cellInfo);

    std::unordered_set<int> visited; // kontener dla już odwiedzonych wierzchołków
    std::queue<int> queue; // kolejka w której zapisujemy wierzchołki do odwiedzenia w kolejnych iteracjach algorytmu

    queue.push(vertex);
    visited.insert(vertex);

    while (not queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();//pobieramy z kolejki pierwszy element
        std::cout << currentVertex << " ";

        for (int neighbour = 0 ; neighbour < adjacencyMatrix[currentVertex].size();neighbour++) {
            if ( adjacencyMatrix[currentVertex][neighbour]
            and visited.find(neighbour) == visited.end()) {// szukamy sąsiadów którzy nie są w liście odwiedzonych
                queue.push(neighbour);//dodajemy sąsiado do kolejki do odwiedzenia
                visited.insert(neighbour);//obecny wierzchołek odznaczamy jako odwiedzony
            }
        }
    }
}

void AdjacencyMatrixGraph::topologicalSortBFS() {
// obliczamy stopien dla krawedzi wchodzacacych dla każdego wierzchołka
    std::vector<int> indegree(adjacencyMatrix.size(), 0);
    for (int i = 0; i < adjacencyMatrix.size() ; ++i) {
        for (int j = 0; j < adjacencyMatrix.size() ; ++j)
            if(adjacencyMatrix[j][i]) indegree[i]++;
    }

    std::queue<int> q;
    std::vector<int> result;

    // kolejkujemy wierzchołki o stopniu wchodzącym 0
    for (int i = 0; i < indegree.size(); ++i)
        if (not indegree[i]) q.push(i);


    while (!q.empty()) {
        int v = q.front();
        q.pop();// pobieramy wierzchołek z kolejki i dodajemy go do posortowanych
        result.push_back(v);


        for (int u = 0 ; u < adjacencyMatrix[v].size();u++) {
            if(!adjacencyMatrix[v][u]) continue;//szukamy wierzchołka z który jest sąsiadem wierzchołka v
            indegree[u]--;//zmniejszamy stopien wejsciowy sasiednich wierzchołkow
            // poniewaz wierzchołek v został juz posortowany
            if (indegree[u] == 0)
                q.push(u);// dodajemy do kolejki sąsiednie wierzchołki
        }
    }

    for (int v : result)
        std::cout << v << " ";

}

void AdjacencyMatrixGraph::topologicalSortDFS() {
    std::stack<int> stack; // stos dla posortowanych wierzchłków
    std::vector<Colour> colours(adjacencyMatrix.size(),White);//tworzymy kontener dla kolorów wierzchołków

    for (int vertex = 0 ; vertex < adjacencyMatrix.size();vertex++)
        if (colours[vertex] == White) DFSUtil(vertex, &colours, stack);// gdy znajdziemy biały wierzchołek
        //wywołujemy rekurencyjną procedurę pomocniczą


    while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
}

void AdjacencyMatrixGraph::DFSUtil(int vertex, std::vector<Colour> * colours, std::stack<int> &stack) {
    (*colours)[vertex] = Grey;// odnaleziony wierzchołek oznaczmy jako szary

    for (int neighbour = 0 ; neighbour <  adjacencyMatrix.size();neighbour++) {
        if ( adjacencyMatrix[vertex][neighbour] and (*colours)[neighbour]==White )//szukamy białych sąsiadów wierchołka
            DFSUtil(neighbour, colours, stack);//rekursyjnie wywołujemy funkcje i przekazujemy sąsiada jako
            //nastepny wierzchołek
    }

    (*colours)[vertex] = Black;
    stack.push(vertex);// wierzchołek uznajemy za posortowany
}


