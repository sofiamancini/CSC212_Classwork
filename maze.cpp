
#include "maze.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

Maze::Maze(int rows, int cols, int seed, std::string filename) 
    : rows(rows), cols(cols), seed(seed), filename(filename) {
    maze.resize(rows, std::vector<std::string>(cols, "1111"));
    std::srand(seed);
    beginMaze();
}


// Maze rules: '0000' means all walls are down, '1111' means all walls are up, '0111' means north wall is down, etc.
void Maze::beginMaze() {
    if (rows == 1 && cols == 1) {
        maze[0][0][1] = '0';
        maze[rows - 1][cols - 1][0] = '0';
        return;
    }
    else {
        maze[0][0] = "0111";
        maze[rows - 1][cols - 1] = "1011";
    }
}


std::pair<int, int> Maze::getNeighbors(int row, int col) {
    std::vector<std::pair<int, int>> neighbors;

    // North
    if (isValid(row - 1, col) && maze[row-1][col] == "1111") {
        neighbors.push_back(std::make_pair(row - 1, col));
    }
    // South
    if (isValid(row + 1, col) && maze[row+1][col] == "1111") {
        neighbors.push_back(std::make_pair(row + 1, col));
    }
    // East
    if (isValid(row, col + 1) && maze[row][col+1] == "1111") {
        neighbors.push_back(std::make_pair(row, col + 1));
    }
    // West
    if (isValid(row, col - 1) && maze[row][col-1] == "1111") {
        neighbors.push_back(std::make_pair(row, col - 1));
    }

    if (!neighbors.empty()) {
        int idx = std::rand() / ((RAND_MAX + 1u) / neighbors.size());
        return neighbors[idx];
    }

    return std::make_pair(-1, -1);
}

bool Maze::isValid(int row, int col) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

void Maze::removeWall(int currRow, int currCol, int nextRow, int nextCol) {
    if (currRow == nextRow) {
        if (currCol < nextCol) {
            // right
            maze[currRow][currCol][2] = '0';
            maze[nextRow][nextCol][3] = '0';
        } else {
            // left
            maze[currRow][currCol][3] = '0';
            maze[nextRow][nextCol][2] = '0';
        }
    } else if (currCol == nextCol) {
        if (currRow < nextRow) {
            // down
            maze[currRow][currCol][1] = '0';
            maze[nextRow][nextCol][0] = '0';
        } else {
            // up
            maze[currRow][currCol][0] = '0';
            maze[nextRow][nextCol][1] = '0';
        }
    }
}

void Maze::generateMaze() {
    std::pair<int, int> current = {0, 0};
    std::vector<std::pair<int, int>> stack;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    stack.push_back(current);
    visited[0][0] = true;

    while (!stack.empty()) {
        current = stack.back();
        stack.pop_back();

        std::vector<std::pair<int, int>> neighbors;
        // North
        if (isValid(current.first - 1, current.second) && !visited[current.first - 1][current.second]) {
            neighbors.push_back(std::make_pair(current.first - 1, current.second));
        }
        //South
        if (isValid(current.first + 1, current.second) && !visited[current.first + 1][current.second]) {
            neighbors.push_back(std::make_pair(current.first + 1, current.second));
        }
        // East
        if (isValid(current.first, current.second + 1) && !visited[current.first][current.second + 1]) {
            neighbors.push_back(std::make_pair(current.first, current.second + 1));
        }
        // West
        if (isValid(current.first, current.second - 1) && !visited[current.first][current.second - 1]) {
            neighbors.push_back(std::make_pair(current.first, current.second - 1));
        }

        if (!neighbors.empty()) {
            stack.push_back(current);
            int idx = std::rand() / ((RAND_MAX + 1u) / neighbors.size());
            std::pair<int, int> next = neighbors[idx];

            removeWall(current.first, current.second, next.first, next.second);
            visited[next.first][next.second] = true;
            stack.push_back(next);
        }
    }
}


void Maze::printMaze() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int num = std::stoi(maze[i][j], nullptr, 2);
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

void Maze::saveMaze() {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int num = std::stoi(maze[i][j], nullptr, 2);
                file << num << " ";
            }
            file << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
}