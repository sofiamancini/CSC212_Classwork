#include "linked_list.h"
#include <iostream>
#include <sstream>

// default constructor
LinkedList::LinkedList(){
    this->head = nullptr;
    this->size = 0;
}

// linked list with one node
LinkedList::LinkedList(int data){
    this->head = new Node(data);
    this->size = 1;
}

// create linked list from vector
LinkedList::LinkedList(std::vector<int> vec){
    this->head = nullptr;
    this->size = 0;
    for(std::vector<int>::size_type i = 0; i < vec.size(); i++){
        this->push_back(vec[i]);
    }
}

// copy constructor
LinkedList::LinkedList(const LinkedList &ll){
    this->head = nullptr;
    this->size = 0;
    Node* tmp = ll.head;
    while(tmp != nullptr){
        this->push_back(tmp->data);
        tmp = tmp->next;
    }
}

// assignment operator
LinkedList& LinkedList::operator=(const LinkedList& other) {
    if (this != &other) {
        this->clear();
        Node* current = other.head;
        while (current != nullptr) {
            this->push_back(current->data);
            current = current->next;
        }
    }
    return *this;
}

// destructor
LinkedList::~LinkedList(){
    this->clear();
}

void LinkedList::clear(){
    Node* tmp = this->head;
    while(tmp != nullptr){
        Node* next = tmp->next;
        delete tmp;
        tmp = next;
    }
    this->head = nullptr;
    this->size = 0;
}

// insert data at head
void LinkedList::push_front(int data){
    Node* new_node = new Node(data);
    new_node->next = this->head;
    this->head = new_node;
    this->size++;
}

// insert data at tail
void LinkedList::push_back(int data){
    Node* new_node = new Node(data);
    if(this->head == nullptr){
        this->head = new_node;
    } else{
        Node* tmp = this->head;
        while(tmp->next != nullptr){
            tmp = tmp->next;
        }
        tmp->next = new_node;
    }
    this->size++;
}

// insert data at index
void LinkedList::insert(int data, int idx){
    if(idx == 0){
        this->push_front(data);
    } else if(static_cast<unsigned int>(idx) >= this->size){
        this->push_back(data);
    } else {
        Node* new_node = new Node(data);
        Node* tmp = this->head;
        for(int i = 0; i < idx - 1; i++){
            tmp = tmp->next;
        }
        new_node->next = tmp->next;
        tmp->next = new_node;
        this->size++;
    }
}

// remove data from the list
void LinkedList::remove(int data){
    Node* tmp = this->head;
    Node* prev = nullptr;

    while(tmp != nullptr){
        if(tmp->data == data){
            if(prev == nullptr){
                this->head = tmp->next;
            } else{
                prev->next = tmp->next;
            }
            delete tmp;
            this->size--;
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

// check if list contains data
bool LinkedList::contains(int data) const {
    Node* tmp = this->head;
    while(tmp != nullptr){
        if(tmp->data == data){
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// get the size of the list
int LinkedList::get_size() const {
    return this->size;
}

// convert list to string
std::string LinkedList::to_string() const {
    std::string stringified;
    Node* tmp = this->head;
    while(tmp != nullptr){
        stringified += std::to_string(tmp->data) + " ";
        tmp = tmp->next;
    }
    return stringified;
}