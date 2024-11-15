#include "node.h"
#include <vector>
#include <string>

class LinkedList{
    private:
        Node* head;
        unsigned int size;

    public:
        LinkedList(); // this->head = nullptr;
        LinkedList(int data);
        LinkedList(std::vector<int> vec);
        LinkedList(const LinkedList &ll);
        LinkedList& operator=(const LinkedList &ll);
        ~LinkedList();

        void push_front(int data);
        void push_back(int data);
        void insert(int data, int idx); // For any `idx` > `size`, append the value
        void remove(int data);
        bool contains(int data) const;
        int get_size() const;
        std::string to_string() const;

    private:
        void clear();
};