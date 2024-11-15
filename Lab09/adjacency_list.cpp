#include "adjacency_list.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>


AdjList::AdjList() {
    this->V = 0;
    this->adj = nullptr;
}

AdjList::~AdjList() {
    if (this->adj != nullptr) {
        delete[] this->adj;
    }
}

void AdjList::resize(int size) {
    std::vector<std::pair<int, int> > *new_adj = new std::vector<std::pair<int, int>>[size + 1];

    if (this->adj != nullptr) {
        for (int i = 0; i <= this->V; i++) {
            new_adj[i] = this->adj[i];
        }
        delete[] this->adj;
    }

    this->adj = new_adj;
    this->V = size;
}

void AdjList::addEdge(int source, int dest, int weight) {
    int max = std::max(source, dest);
    if (max > this->V) {
        this->resize(max);
    }
    this->adj[source].push_back(std::make_pair(dest, weight));
}

void AdjList::printGraph() {
    for (int i = 0; i <= this->V; i++) {
        for (std::pair<int, int> edge : this->adj[i]) {
            std::cout << i << " -> " << edge.first << " : " << edge.second << std::endl;
        }
    }
}

void AdjList::problem1(std::string ofname) {
    std::ofstream ofs(ofname);
    ofs << "digraph G {" << std::endl << std::endl;
    for (int i = 0; i <= this->V; i++) {
        for (std::pair<int, int> edge : this->adj[i]) {
            ofs << i << " -> " << edge.first << " [label=\"" << edge.second << "\"];" << std::endl;
        }
    }
    ofs << std::endl << "}" << std::endl;
}

void AdjList::problem2(std::string ofname) {
    std::ofstream ofs(ofname);
    ofs << "digraph G {" << std::endl << std::endl;
    for (int i = 0; i <= this->V; i++) {
        for (std::pair<int, int> edge : this->adj[i]) {
            if (edge.second % 2 == 0) {
                ofs << "    " << i << " -> " << edge.first << " [label=\"" << edge.second << "\"][color=\"blue\"];" << std::endl;
            } else {
                ofs << "    " << i << " -> " << edge.first << " [label=\"" << edge.second << "\"][color=\"red\"];" << std::endl;
            }
        }
    }
    ofs << std::endl << "}" << std::endl;
}

void AdjList::problem3(std::string ofname) {
    std::ofstream ofs(ofname);
    ofs << "digraph G {" << std::endl << std::endl;
    std::map<int, std::string> colors = {{0, "green"}, {1, "blue"}, {2, "red"}, {3, "purple"}};
    
    for (int i = 0; i <= this->V; i++) {
        int color_index = 0; // Reset color index for each node
        for (const auto& edge : this->adj[i]) {
            std::string color = colors[color_index % 4];
            ofs << i << " -> " << edge.first << " [label=\"" << edge.second << "\"][color=\"" << color << "\"];" << std::endl;
            color_index++;
        }
    }
    ofs << std::endl << "}" << std::endl;
}

void AdjList::problem4(std::string ofname) {
    std::vector<int> tier(this->V + 1, -1);
    std::queue<int> q;
    q.push(0);
    tier[0] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (std::pair<int, int> edge : this->adj[current]) {
            int neighbor = edge.first;
            if (tier[neighbor] == -1) {
                tier[neighbor] = tier[current] + 1;
                q.push(neighbor);
            }
        }
    }

    std::ofstream ofs(ofname);
    ofs << "digraph G {" << std::endl << std::endl;
    std::map<int, std::string> colors = {{0, "green"}, {1, "blue"}, {2, "red"}, {3, "purple"}};

    for (int i = 0; i <= this->V; i++) {
        for (std::pair<int, int> edge : this->adj[i]) {
            int color_index = tier[i] % 4;
            std::string color = colors[color_index];
            ofs << i << " -> " << edge.first << " [label=\"" << edge.second << "\"][color=\"" << color << "\"];" << std::endl;
        }
    }
    ofs << std::endl << "}" << std::endl;
}