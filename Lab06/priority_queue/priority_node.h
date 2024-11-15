#pragma once

class Queue;

class Node{
    private:
        int data;
        int priority;
        Node* next;

        friend class Queue;
        
    public:
        Node();
        // Overloading
        Node(int data, int priority);
        Node(int data, int priority, Node* next);
        ~Node();
};