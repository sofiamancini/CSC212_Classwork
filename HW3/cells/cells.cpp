#include "cells.h"
#include <iostream>
#include <fstream>
using namespace std;


Cells::Cells(const char *fname, int m, int n) {
    rows = m;
    cols = n;

    grid = new bool[rows*cols];
    visited = new bool[rows*cols];

    for (int i = 0; i < rows*cols; i++) {
        visited[i] = false;
    }

    ifstream infile;

    infile.open(fname);

    for(int i = 0; i < rows; i++) {
        int base = i * cols;
        for(int offset = 0; offset < cols; offset++) {
            infile >> grid[base + offset];
        }
    }

    infile.close();
}

Cells::~Cells() {
    delete[] grid;
}

int Cells::countCells(int row, int col, int conn) {
    if (row < 1 || col < 1 || row > rows || col > cols) {
        return 0;
    }

    for (int i = 0; i < rows*cols; i++) {
        visited[i] = false;
    }

    return countCellsHelper(row, col, conn);
}

void Cells::print() {
    for(int i = 0; i < rows; i++) {
        int base = i * cols;
        std::cout << grid[base];
        for(int offset = 1; offset < cols; offset++) {
            std::cout << ' ' << grid[base + offset];
        }
        std::cout << std::endl;
    }
}

int Cells::countCellsHelper(int row, int col, int conn) {

    if (row < 1 || col < 1 || row > rows || col > cols || visited[(row - 1) * cols + (col - 1)] || grid[(row - 1) * cols + (col - 1)] == 0) {
        return 0;
    }

    visited[(row - 1) * cols + (col - 1)] = true;

    int count = 1;

    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {

            if (dr == 0 && dc == 0) continue;

            if (conn == 4 && dr * dc != 0) continue;

            count += countCellsHelper(row + dr, col + dc, conn);
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    int M,N,row, col, conn;

    char *fname = argv[1];

    M = atoi(argv[2]);
    N = atoi(argv[3]);
    row = atoi(argv[4]);
    col = atoi(argv[5]);
    conn = atoi(argv[6]);


    Cells myGrid(fname, M, N);

    cout << myGrid.countCells(row, col, conn) << endl;
    return 0;
}