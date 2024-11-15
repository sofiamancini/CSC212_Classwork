#include "DynamicArray.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

int main(int argc, char* argv[]) {
    DynamicArray da;
    std::string filename;

    if (argc == 2) {
        filename = argv[1];
    } else if (argc == 4) {
        filename = argv[1];

        try {
            double scaling_factor = std::stod(argv[2]);
            unsigned int capacity = std::stoi(argv[3]);
            da = DynamicArray(scaling_factor, capacity);
        } catch (const std::invalid_argument& e) {
            return 1;
        } catch (const std::out_of_range& e) {
            return 1;
        }
    } else {
        return 1;
    }

    // Read integers from a file
    std::vector<int> values;
    std::ifstream file(filename);
    if (!file.is_open()) {
        return 1;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int value;
        while (iss >> value) {
            // Add values to vector
            values.push_back(value);
        }
    }

    if (values.empty()) {
        return 1;
    }

    std::vector<int> values_copy = values;

    // Append 1/2 of integers to the end of the array
    for (unsigned int i = 0; i < values.size() / 2; ++i) {
        da.append(values[i]);
    }
    std::cout << da.to_string() << std::endl;

    // Prepend the other half of integers to the beginning of the array
    for (unsigned int i = values.size() / 2; i < values.size(); ++i) {
        da.prepend(values[i]);
    }
    std::cout << da.to_string() << std::endl;

    // Check that we have enough elements to access the value 1/3 of the way through the original array
    if (values.size() < 3) {
        return 1;
    }

    // Find the first value 1/3 of the way through the original array
    unsigned int index;
    bool foundFirst = da.find_first_of(values[values.size() / 3], &index);
    std::cout << da.fix_format(foundFirst, index) << std::endl;

    // Find the last value 1/3 of the way through the original array
    bool foundLast = da.find_last_of(values[values.size() / 3], &index);
    std::cout << da.fix_format(foundLast, index) << std::endl;

    // Remove the last item from the array
    if (!da.is_empty()) {
        da.remove_last();
        std::cout << da.to_string() << std::endl;
    } else {
        std::cerr << "error" << std::endl;
    }

    // Remove the first item from the array
    if (!da.is_empty()) {
        da.remove_first();
        std::cout << da.to_string() << std::endl;
    } else {
        std::cerr << "error" << std::endl;
    }

    // Clear the array
    da.clear();

    std::cout << da.to_string() << std::endl;

    return 0;
}