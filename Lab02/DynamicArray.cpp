#include "DynamicArray.h"
#include <cstring>

// Default constructor
DynamicArray::DynamicArray() {
    this->m_length = 0;
    this->m_capacity = 1;
    this->m_scaling_factor = 2.0;
    this->m_data = new int[this->m_capacity];
}

// Constructor with capacity
DynamicArray::DynamicArray(double scaling_factor, unsigned int capacity) {
    this->m_length = 0;
    this->m_capacity = capacity;
    this->m_scaling_factor = scaling_factor;
    this->m_data = new int[this->m_capacity];
}

// Constructor with default value
DynamicArray::DynamicArray(double scaling_factor, unsigned int length, int default_value) {
    this->m_length = length;
    this->m_capacity = length;
    this->m_scaling_factor = scaling_factor;
    this->m_data = new int[this->m_capacity];
    for (unsigned int i = 0; i < length; ++i) {
        this->m_data[i] = default_value;
    }
}

// Copy constructor
DynamicArray::DynamicArray(const DynamicArray& other) {
    // Use the assignment operator
    *this = other;
}

// Destructor
DynamicArray::~DynamicArray() {
    delete[] this->m_data;
}

// Assignment operator
DynamicArray& DynamicArray::operator=(const DynamicArray &other) {
    if (this == &other) {
        return *this; // Handle self-assignment
    }
    // Clean up existing resources
    delete[] this->m_data;

    this->m_length = other.m_length;
    this->m_capacity = other.m_capacity;
    this->m_scaling_factor = other.m_scaling_factor;
    this->m_data = new int[this->m_capacity];
    std::memcpy(this->m_data, other.m_data, sizeof(int) * this->m_length);

    return *this;
}

// Clear method: removes values but keeps capacity
void DynamicArray::clear() {
    this->m_length = 0;
}

// Other member functions
unsigned int DynamicArray::get_length() {
    return this->m_length;
}

unsigned int DynamicArray::get_capacity() {
    return this->m_capacity;
}

double DynamicArray::get_scaling_factor() {
    return this->m_scaling_factor;
}

void DynamicArray::set_scaling_factor(double value) {
    this->m_scaling_factor = value;
}

std::string DynamicArray::to_string() {
    std::string str("");
    for (unsigned int i = 0; i < this->m_length; i++) {
        str += std::to_string(this->m_data[i]);
        if (i < this->m_length - 1) {
            str += " ";
        }
    }
    return str;
}

bool DynamicArray::find_first_of(int value, unsigned int *index) {
    for (unsigned int i = 0; i < this->m_length; i++) {
        if (this->m_data[i] == value) {
            *index = i;
            return 1;
        }
    }
    return 0;
}

bool DynamicArray::find_last_of(int value, unsigned int *index) {
    for (int i = this->m_length - 1; i >= 0; --i) { // Note the loop should decrement correctly
        if (this->m_data[i] == value) {
            *index = i;
            return 1;
        }
    }
    return 0;
}

bool DynamicArray::is_empty() {
    return this->m_length == 0;
}

void DynamicArray::append(int value) {
    if (this->m_length == this->m_capacity) {
        this->m_capacity *= this->m_scaling_factor;
        int *new_data = new int[this->m_capacity];
        std::memcpy(new_data, this->m_data, sizeof(int) * this->m_length);
        delete[] this->m_data;
        this->m_data = new_data;
    }
    this->m_data[this->m_length] = value;
    this->m_length++;
}

void DynamicArray::prepend(int value) {
    if (this->m_length == this->m_capacity) {
        this->m_capacity *= this->m_scaling_factor;
        int *new_data = new int[this->m_capacity];
        std::memcpy(new_data + 1, this->m_data, sizeof(int) * this->m_length);
        delete[] this->m_data;
        this->m_data = new_data;
    } else {
        std::memmove(this->m_data + 1, this->m_data, sizeof(int) * this->m_length);
    }
    this->m_data[0] = value;
    this->m_length++;
}

void DynamicArray::remove_last() {
    if (this->m_length > 0) {
        this->m_length--;
    }
}

void DynamicArray::remove_first() {
    if (this->m_length > 0) {
        for (unsigned int i = 0; i < this->m_length - 1; i++) {
            this->m_data[i] = this->m_data[i + 1];
        }
        this->m_length--;
    }
}

int& DynamicArray::operator[](unsigned int index) {
    return this->m_data[index];
}

std::string DynamicArray::fix_format(bool found, unsigned int index) {
    if (found) {
        return "1" + std::string("\t") + std::to_string(index);
    } else {
        return "" + std::string("\t") + std::to_string(index);
    }
}