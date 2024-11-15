#include "blobs.h"
#include <iostream>
#include <fstream>
using namespace std;

Blobs::Blobs(const char *fname, int m, int n) {
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

Blobs::~Blobs() {
    delete[] grid;
}


int Blobs::countBlobs(int row, int col, int conn) {
    int blobCount = 0;
    for (int i = 0; i < rows*cols; i++) {
        visited[i] = false;
    }
    
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            if (!visited[(i - 1) * cols + (j - 1)] && grid[(i - 1) * cols + (j - 1)] == 1) {
                if (countBlobsHelper(i, j, conn) > 0) {
                    blobCount++;
                }
            }
        }
    }
    return blobCount;
}

void Blobs::print() {
    for(int i = 0; i < rows; i++) {
        int base = i * cols;
        std::cout << grid[base];
        for(int offset = 1; offset < cols; offset++) {
            std::cout << ' ' << grid[base + offset];
        }
        std::cout << std::endl;
    }
}

int Blobs::countBlobsHelper(int row, int col, int conn) {
    if (row < 1 || col < 1 || row > rows || col > cols || visited[(row - 1) * cols + (col - 1)] || grid[(row - 1) * cols + (col - 1)] == 0) {
        return 0;
    }

    visited[(row - 1) * cols + (col - 1)] = true;

    int count = 1;

    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;

            if (conn == 4 && dr * dc != 0) continue;

            if (row + dr >= 1 && row + dr <= rows && col + dc >= 1 && col + dc <= cols) {
                count += countBlobsHelper(row + dr, col + dc, conn);
            }
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    int M,N, conn;

    char *fname = argv[1];

    M = atoi(argv[2]);
    N = atoi(argv[3]);
    conn = atoi(argv[4]);


    Blobs myGrid(fname, M, N);

    cout << myGrid.countBlobs(1, 1, conn) << endl;
    return 0;
}