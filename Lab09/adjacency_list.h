#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H
#include <iostream>
#include <vector>
#include <string>

class AdjList{
    public:
        AdjList();
        ~AdjList();
        void addEdge(int source, int dest, int weight);
        void printGraph();
        void resize(int size);
        void problem1(std::string ofname);
        void problem2(std::string ofname);
        void problem3(std::string ofname);
        void problem4(std::string ofname);

    private:
        std::vector<std::pair<int, int> > *adj;
        int V;
};

#endif

