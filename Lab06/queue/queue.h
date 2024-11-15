#include "node.h"
#include <vector>

class Queue{
    private:
        Node* head;
        Node* tail;
        int size;

        void copy(const Queue& q);
        void clear();

    public:
        Queue();
        Queue(int data);
        Queue(std::vector<int> data);
        Queue(const Queue& q);
        ~Queue();
        void enqueue(int data);
        void dequeue();
        int peek();
        void print();
        int getSize() const;
};