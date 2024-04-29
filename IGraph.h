//
// Created by wojciech on 28.04.24.
//

#ifndef UNTITLED16_IGRAPH_H
#define UNTITLED16_IGRAPH_H
#include <vector>
#include <unordered_set>
#include "library.h"

class IGraph {
public:
    virtual void DFS(int vertex = {0} ,std::unordered_set<int> * traversed = nullptr) = 0;
    virtual void DFSWithTimer()=0;
    virtual void BFS(int vertex = 0) = 0;
    virtual void topologicalSortBFS() = 0;
    virtual void topologicalSortDFS() = 0;




protected:
    enum Colour{White,Grey,Black};
    static inline TimeCounter::CellInfo cellInfo;

};


#endif //UNTITLED16_IGRAPH_H
