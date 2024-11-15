#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

struct Point {
    int row, col;
    bool operator<(const Point& other) const {
        return row < other.row || (row == other.row && col < other.col);
    }
};

void findLH(const std::vector<std::vector<int>>& grid, Point& low, Point& high) {
    int min = 101, max = -1;
    int M = grid.size();
    int N = grid[0].size();

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] < min) {
                min = grid[i][j];
                low = {i + 1, j + 1};
            }
            if (grid[i][j] > max) {
                max = grid[i][j];
                high = {i + 1, j + 1};
            }
        }
    }
}

bool isValid(int row, int col, int M, int N) {
    return row >= 0 && row < M && col >= 0 && col < N;
}

bool bfs(const std::vector<std::vector<int>>& grid, const Point& low, const Point& high) {
    int M = grid.size();
    int N = grid[0].size();
    std::vector<std::vector<bool>> visited(M, std::vector<bool>(N, false));
    std::queue<Point> q;
    q.push({low.row - 1, low.col - 1});
    visited[low.row - 1][low.col - 1] = true;

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        if (curr.row == high.row - 1 && curr.col == high.col - 1) {
            return true;
        }

        for (auto& d : directions) {
            int newRow = curr.row + d[0];
            int newCol = curr.col + d[1];

            if (isValid(newRow, newCol, M, N) && !visited[newRow][newCol] && grid[newRow][newCol] >= grid[curr.row][curr.col]) {
                visited[newRow][newCol] = true;
                q.push({newRow, newCol});
            }
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    std::string fname = argv[1];
    int M = std::stoi(argv[2]);
    int N = std::stoi(argv[3]);

    std::ifstream file(fname);
    std::vector<std::vector<int>> grid(M, std::vector<int>(N));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            file >> grid[i][j];
        }
    }
    file.close();

    Point low, high;
    findLH(grid, low, high);
    bool exists = bfs(grid, low, high);
    std::cout << low.row << " " << low.col << " " << high.row << " " << high.col << " " << (exists ? "yes" : "no") << std::endl;

    return 0;
}