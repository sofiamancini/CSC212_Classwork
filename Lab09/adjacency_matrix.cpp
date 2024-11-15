#include "adjacency_matrix.h"
#include <iostream>
#include <fstream>
#include <sstream>

AdjMatrix::AdjMatrix() {
    this->V = 0;
    this->adj = nullptr;
}

AdjMatrix::~AdjMatrix() {
    if (this->adj != nullptr) {
        for (int i = 0; i <= this->V; i++) {
            delete[] this->adj[i];
        }
        delete[] this->adj;
    }
}

void AdjMatrix::resize(int size) {

    int **new_adj = new int*[size + 1];
    for (int i = 0; i <= size; i++) {
        new_adj[i] = new int[size + 1];
        for (int j = 0; j <= size; j++) {
            new_adj[i][j] = 0;
        }
    }
   
    if (this->adj != nullptr) {
        for (int i = 0; i <= this->V; i++) {
            for (int j = 0; j <= this->V; j++) {
                new_adj[i][j] = this->adj[i][j];
            }
        }
        for (int i = 0; i <= this->V; i++) {
            delete[] this->adj[i];
        }
        delete[] this->adj;
    }

    this->adj = new_adj;
    this->V = size;
}

void AdjMatrix::addEdge(int source, int dest, int weight) {
    int max = std::max(source, dest);
    if (max > this->V) {
        this->resize(max);
    }
    this->adj[source][dest] = weight;
}

void AdjMatrix::printGraph() {
    for (int i = 0; i <= this->V; i++) {
        for (int j = 0; j <= this->V; j++) {
            std::cout << this->adj[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void AdjMatrix::outputGraph(std::string ofname) {
    std::ofstream ofs(ofname);
    ofs << "digraph G {" << std::endl << std::endl;
    for (int i = 0; i <= this->V; i++) {
        for (int j = 0; j <= this->V; j++) {
            if (this->adj[i][j] != 0) {
                ofs << "    " << i << " -> " << j << " [label=\"" << this->adj[i][j] << "\"];" << std::endl;
            }
        }
    }
    ofs << std::endl << "}" << std::endl;
}