#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <unordered_set>
#include <set>
#include <limits>

struct Point {
    double lat, lon;
    Point(double lat = 0, double lon = 0) : lat(lat), lon(lon) {}
};

struct NationalPark {
    std::string name;
    Point location;
    NationalPark(const std::string& name = "", const Point& location = Point()) 
        : name(name), location(location) {}
};

struct Edge {
    int from;
    int to;
    std::string label;

    bool operator<(const Edge& other) const {
        return std::tie(from, to, label) < std::tie(other.from, other.to, other.label);
    }
};

class KDTNode {
private:
    NationalPark park;
    KDTNode* left;
    KDTNode* right;
    std::string id;

public:
    KDTNode(const NationalPark& park, const std::string& id);
    ~KDTNode();

    friend class KDTree;
};

class KDTree {
private:
    KDTNode* root;
    std::set<Edge> path;
    int nodeCount;
    int nearestNodeId;

public:
    KDTree(const std::vector<NationalPark>& parks);
    ~KDTree();
    NationalPark findNearest(const Point& target);
    void insert(const NationalPark& park);
    void DOTFile(const std::string& filename);

private:
    KDTNode* buildTree(std::vector<NationalPark> parks, int depth);
    void destroy(KDTNode* node);
    void findNearestHelper(KDTNode* node, const Point& target, NationalPark& best, double& bestDist, int depth, std::unordered_set<int>& visited);
    KDTNode* insertHelper(KDTNode* node, const NationalPark& park, int depth);
    static double distance(const Point& a, const Point& b);
};

#endif