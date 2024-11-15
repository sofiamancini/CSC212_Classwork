#include "kdtree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

// returns true if the line is a valid insert command
bool checkInsert(const std::string& line, NationalPark& park) {
    std::stringstream ss(line);
    std::string command, name, city, state;
    double lat, lon;

    ss >> command;
    std::getline(ss >> std::ws, name, ',');
    std::getline(ss >> std::ws, city, ',');
    ss >> state >> lat >> lon;

    park = {name + ", " + city + ", " + state, {lat, lon}};
    return true;
}

// returns true if the line is a valid find command
bool checkFind(const std::string& line, Point& target) {
    std::stringstream ss(line);
    std::string command;
    double lat, lon;

    ss >> command >> lat >> lon;
    target = {lat, lon};
    return true;
}

int main(int argc, char* argv[]) {

    std::string datasetFile = argv[1];
    std::string commandsFile = argv[2];
    unsigned long c_start, c_end;

    std::ifstream infile(datasetFile);

    // Read the dataset file and stores the data in a vector of NationalPark
    std::vector<NationalPark> parks;
    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string name, city, state;
        double lat, lon;

        std::getline(ss, name, ',');
        std::getline(ss, city, ',');
        ss >> state >> lat >> lon;

        parks.push_back({name + ", " + city + ", " + state, {lat, lon}});
    }

    KDTree tree(parks);

    // Read the commands file and process the commands
    std::ifstream commands(commandsFile);

    while (std::getline(commands, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "insert") {
            NationalPark park;
            if (!checkInsert(line, park)) {
                continue;
            }
            tree.insert(park);
            std::cout << "Inserted: " << park.name << std::endl;
        } else if (command == "find") {
            Point target;
            if (!checkFind(line, target)) {
                continue;
            }
            
            c_start = std::clock();
            NationalPark nearestPark = tree.findNearest(target);
            c_end = std::clock();
            float time = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
            std::cout << "Nearest: " << nearestPark.name << std::endl;
            tree.DOTFile("DOT_find.dot");
        }
    }

    return 0;
}