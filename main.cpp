#include "maze.h"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <rows> <cols> <seed> <filename>" << std::endl;
        return 1;
    }

    int seed = std::stoi(argv[1]);
    int rows = std::stoi(argv[2]);
    int cols = std::stoi(argv[3]);
    std::string filename = argv[4];

    Maze maze(rows, cols, seed, filename);
    maze.generateMaze();
    maze.printMaze();
    maze.saveMaze();

    return 0;
}