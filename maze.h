// Header file for maze code

#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Maze {
    private:
        std::vector<std::vector<std::string>> maze;
        void beginMaze();
        void removeWall(int currRow, int currCol, int nextRow, int nextCol);
        std::pair<int, int> getNeighbors(int row, int col);
        bool isValid(int row, int col);
    public:
        int rows, cols, seed;
        std::string filename;

        Maze(int rows, int cols, int seed, std::string filename);
        void generateMaze();
        void printMaze();
        void saveMaze();
};

#endif