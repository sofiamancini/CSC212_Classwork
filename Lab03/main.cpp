#include "linked_list.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

int main(int argc, char* argv[]) {
    std::ifstream file(argv[1]);
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    std::vector<int> vec;
    int num;
    while(ss >> num) {
        vec.push_back(num);
    }
    LinkedList ll;

    if (vec.size() == 0) {
        ll = LinkedList();
    } else if (vec.size() == 1) {
        ll = LinkedList(vec[0]);
    } else {
        ll = LinkedList(vec);
    }

    std::cout << ll.to_string() << std::endl;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int data, idx;
        bool checkLine = (ss >> data) && (ss.peek() == EOF);
        // case 1: single integer on line
        if (checkLine) {
            // case 3: negative integer on line
            if (data < 0) {
                ll.remove(std::abs(data));
            } else {
                if (data % 2 == 0) {
                    ll.push_back(data);
                } else {
                    ll.push_front(data);
                }
            }
            std::cout << ll.to_string() << std::endl;
        } else if (ss >> idx) {
            // case 2: two integers on line
            ll.insert(data, idx);
            std::cout << ll.to_string() << std::endl;
        }

        // case 4: line contains '?'
        if (line.find('?') != std::string::npos) {
            std::cout << ll.contains(data) << std::endl;
        }
    }

    return 0;
}