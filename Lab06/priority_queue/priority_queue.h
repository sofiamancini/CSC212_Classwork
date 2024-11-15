#include "priority_node.h"
#include <vector>

class Queue{
    private:
        Node* head;
        int size;

        void copy(const Queue& q);
        void clear();

    public:
        Queue();
        Queue(int data, int priority);
        Queue(const std::vector<int>& data, const std::vector<int>& prio);
        Queue(const Queue& q);
        Queue& operator=(const Queue& q);
        ~Queue();
        void enqueue(int data, int priority);
        void dequeue();
        int peek();
        void print();
};