#ifndef adjacency_matrix_h
#define adjacency_matrix_h
#include <iostream>
#include <vector>

class AdjMatrix{
    public:
        AdjMatrix();
        ~AdjMatrix();
        void addEdge(int source, int dest, int weight);
        void printGraph();
        void outputGraph(std::string ofname);
    private:
        void resize(int size);
        int **adj;
        int V;
};

#endif