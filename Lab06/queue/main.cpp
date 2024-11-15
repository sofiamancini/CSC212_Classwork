#include "queue.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


int main(int argc, char* argv[]){
    std::ifstream file(argv[1]);

    Queue q;

    
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    std::vector<int> data;
    int temp;
    while(ss >> temp){
        data.push_back(temp);
    }
    

    if (data.size() == 0){
        q = Queue();
    } else {
        for(int value : data){
        q.enqueue(value);
        }
    }
 
    q.print();

    while (std::getline(file, line)){
        // if line is an integer, enqueue
        if (std::isdigit(line[0]) || (line[0] == '-' && line.size() > 1 && std::isdigit(line[1]))) {
            int num = std::stoi(line);
                q.enqueue(num);
                q.print();
        // if line is '-', dequeue
        } else if (line == "-"){
            q.dequeue();
            q.print();
        // if line is '?', peek
        } else if (line == "?"){
            std::cout << q.peek() << std::endl;
        }

    }

    return 0;
}