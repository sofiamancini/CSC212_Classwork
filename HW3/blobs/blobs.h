#ifndef _BLOBS_
#define _BLOBS_

class Blobs {
    private:
        int rows, cols;
        bool *grid;
        bool *visited;
        int countBlobsHelper(int row, int col, int conn);
    public:
        Blobs(const char *fname, int m, int n);
        ~Blobs();
        int countBlobs(int row, int col, int conn);
        void print();
};
#endif