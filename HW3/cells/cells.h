#ifndef _CELLS_
#define _CELLS_

class Cells {
    private:
        int rows, cols;
        bool *grid;
        bool *visited;
        int countCellsHelper(int row, int col, int conn);
    public:

        Cells(const char *fname, int m, int n);
        ~Cells();
        int countCells(int row, int col, int conn);
        void print();
};
#endif