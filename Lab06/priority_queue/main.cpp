#include "priority_queue.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

bool isNum(const std::string& s) {
    if (s.empty()) return false;
    for (size_t i = 0; i < s.size(); i++) {
        if (!std::isdigit(s[i]) && s[i] != '-') return false;
    }
    return true;
}

int main(int argc, char* argv[]) {

    std::ifstream file(argv[1]);

    Queue q;

    std::string line;
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<int> data;
        std::vector<int> prio;
        int temp, index = 0;
        while (ss >> temp) {
            data.push_back(temp);
            prio.push_back(index++);
        }
        if (!data.empty()) {
            q = Queue(data, prio);
        }
        q.print();
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string first, second;
        ss >> first >> second;

        if (first.empty()) continue;

        if (first == "-") {
            q.dequeue();
            q.print();
        } else if (isNum(first)) {
            try {
                int num = std::stoi(first);
                int prio = std::stoi(second);
                q.enqueue(num, prio);
                q.print();
            } catch (const std::invalid_argument& e) {
                return 1;
            }
        } else if (first == "?") {
            q.peek();
        }
    }


    return 0;
}