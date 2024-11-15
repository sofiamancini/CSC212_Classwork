#include "queue.h"
#include <iostream>

// Default constructor
Queue::Queue() : head(nullptr), tail(nullptr), size(0) {}

// Constructor with multiple nodes
Queue::Queue(const std::vector<int> data){
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
    for(int value : data){
        this->enqueue(value);
    }
}

// Copy constructor
Queue::Queue(const Queue& q) : head(nullptr), tail(nullptr), size(0){
    this->copy(q);
}

// Destructor
Queue::~Queue(){
    this->clear();
}

void Queue::copy(const Queue& q){
    Node* temp = q.head;
    while(temp != nullptr){
        this->enqueue(temp->data);
        temp = temp->next;
    }
}


void Queue::clear(){
    while(this->head != nullptr){
        Node* temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
    this->tail = nullptr;
    this->size = 0;
}

// Enqueue
void Queue::enqueue(int data){
    Node* newNode = new Node(data);
    if(this->head == nullptr){
        this->head = newNode;
        this->tail = newNode;
    }else{
        this->tail->next = newNode;
        this->tail = newNode;
    }
    this->size++;
}

// Dequeue
void Queue::dequeue(){
    if(this->head != nullptr){
        Node* temp = this->head;
        this->head = this->head->next;
        delete temp;
        if(this->head == nullptr){
            this->tail = nullptr;
        }
        this->size--;
    }
}

// Peek
int Queue::peek(){
    if (this->head != nullptr){
        return this->head->data;
    }
}

// Print
void Queue::print(){
    Node* temp = this->head;
    while(temp != nullptr){
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

// Get size
int Queue::getSize() const{
    return this->size;
}