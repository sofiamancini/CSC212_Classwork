#include "n_queens.h"

NQueens::NQueens(){
    this->board_size = 0;
    this->board = nullptr;
}

NQueens::~NQueens(){
    delete this->board;
}

NQueens::NQueens(unsigned int n){
    this->board_size = n;

    board = new std::vector<std::vector<unsigned int >>(n, std::vector<unsigned int>(n));
}

bool NQueens::solve_rec(int col){
    if (col >= this->board_size) { return true; }

    for (unsigned int i = 0; i < this->board_size; i++) {
        if (is_valid_row(i, col)) {
            (*this->board)[i][col] = 1;

            if (solve_rec(col + 1)) { return true; }

            (*this->board)[i][col] = 0;
        }
    }

    return false;
}


bool NQueens::is_valid_row(unsigned int row, unsigned int col){
    int i, j;

    /* Check this row on left side */
    for (i = 0; i < col; i++)
        if ((*this->board)[row][i]) { return false; }

    /* Check upper diagonal on left side */
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if ((*this->board)[i][j]) { return false; }

    /* Check lower diagonal on left side */
    for (i = row, j = col; j >= 0 && i < this->board_size; i++, j--)
        if ((*this->board)[i][j]) { return false; }

    return true;
}

void NQueens::display_board(){
    for (unsigned int i = 0; i < this->board_size; i++) {
        for (unsigned int j = 0; j < this->board_size; j++){
            std::cout << (*this->board)[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char*argv[])
{
    unsigned int n = std::stoi(argv[1]);

    NQueens Q(n);

    Q.solve_rec(0);

    Q.display_board();

    return 0;
}