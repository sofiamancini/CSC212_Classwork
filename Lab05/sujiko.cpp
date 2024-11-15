#include "sujiko.h"

Sujiko::Sujiko() {
    board = std::vector<std::vector<unsigned int> >(BOARD_SIZE, std::vector<unsigned int>(BOARD_SIZE, EMPTY));
    nums = std::vector<std::vector<unsigned int> >(2, std::vector<unsigned int>(2, EMPTY));
    used = std::vector<bool>(10, false);

}

Sujiko::Sujiko(std::string fname) {
    // Read 4 sum values from file
    // Read file & create board
    std::ifstream file(fname);
    nums = std::vector<std::vector<unsigned int> >(2, std::vector<unsigned int>(2, EMPTY));
    for (unsigned int i = 0; i < 2; i++) {
        for (unsigned int j = 0; j < 2; j++) {
            file >> (this->nums)[i][j];
        }
    }

    board = std::vector<std::vector<unsigned int> >(BOARD_SIZE, std::vector<unsigned int>(BOARD_SIZE, EMPTY));
    used = std::vector<bool>(10, false);

    for (unsigned int i = 0; i < BOARD_SIZE; i++) {
        for (unsigned int j = 0; j < BOARD_SIZE; j++){
            file >> (this->board)[i][j];
            if ((this->board)[i][j] != EMPTY) {
                used[(this->board)[i][j]] = true;
            }
        }
    }
    file.close();
}

Sujiko::~Sujiko() {

}

bool Sujiko::solve(unsigned int cell){
    // If the sum of the 4 cells is equal to the sum value, return true
    if (cell == BOARD_SIZE * BOARD_SIZE) {
        return (this->board)[0][0] + (this->board)[0][1] + (this->board)[1][0] + (this->board)[1][1] == (this->nums)[0][0] &&
               (this->board)[0][1] + (this->board)[0][2] + (this->board)[1][1] + (this->board)[1][2] == (this->nums)[0][1] &&
               (this->board)[1][0] + (this->board)[1][1] + (this->board)[2][0] + (this->board)[2][1] == (this->nums)[1][0] &&
               (this->board)[1][1] + (this->board)[1][2] + (this->board)[2][1] + (this->board)[2][2] == (this->nums)[1][1];
    }
    // Backtracking
    unsigned int row = cell / this->BOARD_SIZE;
    unsigned int col = cell % this->BOARD_SIZE;
    if ((this->board)[row][col] != EMPTY) {
        return solve(cell + 1);
    }
    for (unsigned int num = 1; num <= 9; num++) {
        if (!used[num]) {
            (this->board)[row][col] = num;
            used[num] = true;
            if (solve(cell + 1)) {
                return true;
            }
            (this->board)[row][col] = EMPTY;
            used[num] = false;
        }
    }
    return false;
}

void Sujiko::display_board(){
    for (unsigned int i = 0; i < this->BOARD_SIZE; i++) {
        for (unsigned int j = 0; j < this->BOARD_SIZE; j++){
            std::cout << this->board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char * argv[])
{
    Sujiko s(argv[1]);

    s.solve(0);

    s.display_board();

    return 0;
}