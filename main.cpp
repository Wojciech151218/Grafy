#include <iostream>
#include "EdgeListGraph.h"
#include <random>
#include "library.h"

#include <vector>
#include "AdjacencyListGraph.h"
#include "AdjacencyMatrixGraph.h"
int generateRandomInteger(int min, int max) {
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the random number generator
    std::uniform_int_distribution<> dis(min, max); // Define the range

    return dis(gen); // Generate and return a random integer
}
bool getRandomBool(double probability){
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the random number generator

    // Define a distribution to generate numbers between 0 and 1
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Generate a random number
    double randNum = dis(gen);

    // Compare with probability to determine the result
    return randNum < probability;
}
std::vector<std::vector<bool>> getRandomMatrix(int size){
    int edgeAmount = (size-1)*size/4 ;
    int availableCells = size*(size-1)/2;
    double probability = double(edgeAmount)/double(availableCells);
    //diagonala macierzy nie może być pełna elementy macierzy będą indeksowane od 1 elementu a nie elementu 0
    //np tak:
    //x 1 0 1
    //x x 1 0
    //x x x 1
    //x x x x
    std::vector<std::vector<bool>> result;
    for (int i = 0; i < size-1; ++i) {
        std::vector<bool> temp;
        //temp.push_back(true); // pierwszy element jest zapełniony po to by mieć pewność że graf będzie spójny
        for (int j = 0; j < size-i-1; ++j) {
            temp.push_back(getRandomBool(probability));
        }
        int randomInt = generateRandomInteger(0, size-i-2);
        temp[randomInt] = true;// losowy element jest zapełniony po to by mieć pewność że graf będzie spójny
        result.push_back(temp);
    }
    return result;

}

std::vector<AdjacencyListGraph*> adjacencyListGraphs;
std::vector<EdgeListGraph*> edgeListGraphs;


int main() {
    /*auto randomMatrix = getRandomMatrix(10);

    AdjacencyListGraph aLGraph(randomMatrix);
    EdgeListGraph eLGraph(randomMatrix);
    AdjacencyMatrixGraph amGraph(randomMatrix);

    printf("DFS dla listy następników: "); aLGraph.DFSWithTimer();
    printf("\nBFS dla listy następników: "); aLGraph.BFS();
    printf("\nsortowanie topologiczne BFS dla listy następników: "); aLGraph.topologicalSortBFS();
    printf("\nsortowanie topologiczne DFS dla listy następników: "); aLGraph.topologicalSortDFS();
    printf("\n");printf("\n");

    printf("DFS dla listy krawędzi: "); eLGraph.DFSWithTimer();
    printf("\nBFS dla listy krawędzi: "); eLGraph.BFS();
    printf("\nsortowanie topologiczne BFS dla listy krawędzi: ");eLGraph.topologicalSortBFS();
    printf("\nsortowanie topologiczne DFS dla listy krawędzi: ");eLGraph.topologicalSortDFS();
    printf("\n"); printf("\n");

    printf("DFS dla macierzy sąsiedztwa: "); amGraph.DFSWithTimer();
    printf("\nBFS dla macierzy sąsiedztwa: "); amGraph.BFS();
    printf("\nsortowanie topologiczne BFS dla macierzy sąsiedztwa: ");amGraph.topologicalSortBFS();
    printf("\nsortowanie topologiczne DFS dla macierzy sąsiedztwa: ");amGraph.topologicalSortDFS();
    printf("\n"); printf("\n");
    return 0;


*/
    std::vector<IGraph*> graphs;
    TimeCounter::generateDirectory("/home/wojciech/CLionProjects/untitled16");

    std::string bfsTopologicalName = "sortowanie_topologiczne_BFS";
    std::string bfsName = "przeglądanie_BFS";
    std::string dfsTopologicalName = "sortowanie_topologiczne_DFS";
    std::string dfsName = "przeglądanie_DFS";

    std::string adjacencyMatrixName = "macierz_sąsiedztwa";
    std::string adjacencyListName = "lista_następników";
    std::string edgeListName = "Lista_krawędzi";


    TimeCounter::addColumnNames({adjacencyListName,adjacencyMatrixName,edgeListName});

    std::vector<int> sizes ;
    for(int i=1;i<=10;i++)
        sizes.push_back(i*20);


    for(auto &&it :sizes){
        TimeCounter::addIndex(it);
        auto matrix = getRandomMatrix(it);
        graphs.push_back(new AdjacencyListGraph(matrix));
        graphs.push_back(new EdgeListGraph(matrix));
        graphs.push_back(new AdjacencyMatrixGraph(matrix));
    }

    int size = 0;
    TimeCounter::addFileName(dfsName);
    for (auto it = graphs.begin(); it!=graphs.end();it++) {
        AdjacencyListGraph::updateCellInfo({sizes[size],adjacencyListName});
        (*it)->DFSWithTimer();
        EdgeListGraph::updateCellInfo({sizes[size],edgeListName});
        (*it++)->DFSWithTimer();
        AdjacencyMatrixGraph::updateCellInfo({sizes[size++],adjacencyMatrixName});
        (*it++)->DFSWithTimer();
    }
    TimeCounter::generateFile();
    size = 0;
    TimeCounter::addFileName(bfsName);
    for (auto it = graphs.begin(); it!=graphs.end();it++) {
        AdjacencyListGraph::updateCellInfo({sizes[size],adjacencyListName});
        (*it)->BFS();
        EdgeListGraph::updateCellInfo({sizes[size],edgeListName});
        (*it++)->BFS();
        AdjacencyMatrixGraph::updateCellInfo({sizes[size++],adjacencyMatrixName});
        (*it++)->BFS();
    }
    TimeCounter::generateFile();
    size = 0;
    TimeCounter::addFileName(dfsTopologicalName);
    for (auto it = graphs.begin(); it!=graphs.end();it++) {
        AdjacencyListGraph::updateCellInfo({sizes[size],adjacencyListName});
        (*it)->topologicalSortDFS();
        EdgeListGraph::updateCellInfo({sizes[size],edgeListName});
        (*it++)->topologicalSortDFS();
        AdjacencyMatrixGraph::updateCellInfo({sizes[size++],adjacencyMatrixName});
        (*it++)->topologicalSortDFS();
    }
    TimeCounter::generateFile();
    size = 0;
    TimeCounter::addFileName(bfsTopologicalName);
    for (auto it = graphs.begin(); it!=graphs.end();it++) {
        AdjacencyListGraph::updateCellInfo({sizes[size],adjacencyListName});
        (*it)->topologicalSortBFS();
        EdgeListGraph::updateCellInfo({sizes[size],edgeListName});
        (*it++)->topologicalSortBFS();
        AdjacencyMatrixGraph::updateCellInfo({sizes[size++],adjacencyMatrixName});
        (*it++)->topologicalSortBFS();
    }
    TimeCounter::generateFile();
    size = 0;




    TimeCounter::generateExcelSheet("/home/wojciech/CLionProjects/untitled16/generateExcel.py");

    return 0;
}