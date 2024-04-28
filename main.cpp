#include <iostream>
#include "EdgeListGraph.h"
#include <random>
#include "library.h"

#include <vector>
#include "AdjacencyListGraph.h"
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
    int edgeAmount = (size-1)*size/4;
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
        temp[generateRandomInteger(0, size-i-1)] = true;// losowy element jest zapełniony po to by mieć pewność że graf będzie spójny
        result.push_back(temp);
    }
    return result;

}

std::vector<AdjacencyListGraph*> adjacencyListGraphs;
std::vector<EdgeListGraph*> edgeListGraphs;



int main() {
    auto randomMatrix = getRandomMatrix(10);

    AdjacencyListGraph aLGraph(randomMatrix);
    EdgeListGraph eLGraph(randomMatrix);

    aLGraph.DFSWithTimer();
    printf("\n");
    aLGraph.BFS();
    printf("\n");
    aLGraph.topologicalSortBFS();
    printf("\n");
    aLGraph.topologicalSortDFS();
    printf("\n");
    printf("\n");

    eLGraph.DFSWithTimer();
    printf("\n");
    eLGraph.BFS();
    printf("\n");
    eLGraph.topologicalSortBFS();
    printf("\n");
    eLGraph.topologicalSortDFS();
    printf("\n");


    return 0;
    /*
    TimeCounter::generateDirectory("/home/wojciech/CLionProjects/untitled16");

    std::string bfsTopologicalName = "sortowanie_topologiczne_BFS";
    std::string bfsName = "przeglądanie_BFS";
    std::string dfsTopologicalName = "sortowanie_topologiczne_DFS";
    std::string dfsName = "przeglądanie_DFS";

    TimeCounter::addColumnNames({bfsName,bfsTopologicalName,dfsName,dfsTopologicalName});

    std::vector<int> sizes ;
    for(int i=1;i<=10;i++)
        sizes.push_back(i*20);


    for(auto &&it :sizes){
        TimeCounter::addIndex(it);
        auto matrix = getRandomMatrix(it);
        adjacencyListGraphs.push_back(new AdjacencyListGraph(matrix));
        edgeListGraphs.push_back(new EdgeListGraph(matrix));
    }

    int size = 0;
    TimeCounter::addFileName("Lista_sąsiedztwa");
    for(auto&& graph:adjacencyListGraphs){
        AdjacencyListGraph::updateCellInfo({sizes[size],bfsName});
        graph->BFS();
        AdjacencyListGraph::updateCellInfo({sizes[size++],dfsName});
        graph->DFSWithTimer();
    }
    TimeCounter::generateFile();

    size = 0;
    TimeCounter::addFileName("Lista_krawędzi");
    for(auto&& graph:edgeListGraphs){
        EdgeListGraph::updateCellInfo({sizes[size],bfsName});
        graph->BFS();
        EdgeListGraph::updateCellInfo({sizes[size++],dfsName});
        graph->DFSWithTimer();
    }
    size = 0;

    TimeCounter::generateFile();
    TimeCounter::generateExcelSheet("/home/wojciech/CLionProjects/untitled16/generateExcel.py");

    return 0;

    */
}