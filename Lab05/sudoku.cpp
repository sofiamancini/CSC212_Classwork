#include "sudoku.h"
#include <sstream>
#include <fstream>
#include <iostream>

Sudoku::Sudoku() {
    for (unsigned int i = 0; i < this->BOARD_SIZE; i++) {
        for (unsigned int j = 0; j < this->BOARD_SIZE; j++){
            (this->board)[i][j] = EMPTY;
        }
    }

}

Sudoku::~Sudoku() {

}

Sudoku::Sudoku(std::string f_name) {
    // Generate a board from the give file
    std::ifstream file(f_name);
    std::string line;
    unsigned int row = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        unsigned int col = 0;
        int num;
        while (iss >> num) {
            (this->board)[row][col] = num;
            col++;
        }
        row++;
    }
    file.close();
}

bool Sudoku::solveHelper(int row, int col){
    if (row == BOARD_SIZE) {
        row = 0;
        if (++col == BOARD_SIZE) {
            return true;
        }
    }

    if ((this->board)[row][col] != EMPTY) {
        return solveHelper(row + 1, col);
    }

    for (int num = 1; num <= BOARD_SIZE; num++) {
        if (is_valid(row, col, num)) {
            (this->board)[row][col] = num;
            if (solveHelper(row + 1, col)) {
                return true;
            }
            (this->board)[row][col] = EMPTY;
        }
    }

    return false;
}

void Sudoku::solve() {
    solveHelper(0, 0);
}


// If this is an empty space & the given number does not exist in the same
// row, column, or box then it will return true.
bool Sudoku::is_valid(unsigned int row, unsigned int col, int num){
    return (this->board)[row][col] == EMPTY
            && !check_row(row, num)
            && !check_col(col, num)
            && !check_box(row - row % 3, col - col % 3, num);
}

bool Sudoku::check_row(unsigned int row, unsigned int num){
    for (int i = 0; i < BOARD_SIZE; i++) {
        if ((this->board)[row][i] == num) {
            return true;
        }
    }
    return false;
}

bool Sudoku::check_col(unsigned int col, unsigned int num){
    for (int i = 0; i < BOARD_SIZE; i++) {
        if ((this->board)[i][col] == num) {
            return true;
        }
    }

    return false;
}

bool Sudoku::check_box(unsigned int boxStartRow, unsigned int boxStartCol, unsigned int num){
    for (int row = 0; row < (BOARD_SIZE / 3); row++) {
        for (int col = 0; col < (BOARD_SIZE / 3); col++) {
            if ((this->board)[row + boxStartRow][col + boxStartCol] == num) {
                return true;
            }
        }
    }

    return false;
}

void Sudoku::display_board(){
    for (unsigned int i = 0; i < this->BOARD_SIZE; i++) {
        for (unsigned int j = 0; j < this->BOARD_SIZE; j++){
            std::cout << (this->board)[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char * argv[])
{
    std::string f_name(argv[1]);

    Sudoku s(f_name);

    s.solve();

    s.display_board();

    return 0;
}