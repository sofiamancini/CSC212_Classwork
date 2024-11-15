#include "priority_queue.h"
#include <iostream>

// Default constructor
Queue::Queue() : head(nullptr), size(0) {}

// Constructor with single node
Queue::Queue(int data, int priority){
    this->head = new Node(data, priority);
    this->size = 1;
}

// Constructor with multiple nodes
Queue::Queue(const std::vector<int>& data, const std::vector<int>& prio){
    this->head = nullptr;
    this->size = 0;
    for(size_t i = 0; i < data.size(); i++){
        this->enqueue(data[i], prio[i]);
    }
}

// Copy constructor
Queue::Queue(const Queue& q) : head(nullptr), size(0){
    this->copy(q);
}

// Assignment operator
Queue& Queue::operator=(const Queue& q){
    if(this == &q){
        return *this;
    }
    this->clear();
    this->copy(q);
    return *this;
}

// Destructor
Queue::~Queue(){
    this->clear();
}

void Queue::copy(const Queue& q){
    Node* temp = q.head;
    while(temp != nullptr){
        this->enqueue(temp->data, temp->priority);
        temp = temp->next;
    }
}


void Queue::clear(){
    while(this->head != nullptr){
        Node* temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
    this->size = 0;
}

// Enqueue
void Queue::enqueue(int data, int priority){
    Node* newNode = new Node(data, priority);
    if(this->head == nullptr || this->head->priority > priority){
        newNode->next = this->head;
        this->head = newNode;
    } else {
        Node* temp = this->head;
        while(temp->next != nullptr && temp->next->priority <= priority){
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    this->size++;
}

// Dequeue
void Queue::dequeue(){
    if(this->head != nullptr){
        Node* temp = this->head;
        this->head = this->head->next;
        delete temp;
        this->size--;
    }
}

// Peek
int Queue::peek(){
    if (this->head != nullptr){
        std::cout << "(" << this->head->data << "," << this->head->priority << ")" << std::endl;
        return this->head->data;
    } else {
        std::cout << std::endl;
        return 0;
    }
}

// Print
void Queue::print(){
    Node* temp = this->head;
    while(temp != nullptr){
        std::cout << " (" << temp->data << "," << temp->priority << ")";
        temp = temp->next;
    }
    std::cout << std::endl;
}