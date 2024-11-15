#include "kdtree.h"

// KD Node Constructor
KDTNode::KDTNode(const NationalPark& park, const std::string& id) : park(park), left(nullptr), right(nullptr), id(id) {}

// KD Node Destructor
KDTNode::~KDTNode() {
    // delete left;
    // delete right;
}

// KD Tree constructor using build tree function
KDTree::KDTree(const std::vector<NationalPark>& parks) {
    root = buildTree(parks, 0);
    nodeCount = 0;
    nearestNodeId = -1; // Initialize the nearest node ID
}

// KD Tree destructor
KDTree::~KDTree() {
    destroy(root);
}

KDTNode* KDTree::buildTree(std::vector<NationalPark> parks, int depth) {
    int axis = depth % 2;

    if (parks.empty()) return nullptr;

    // Sort the vector based on the current axis, sort function sorts parks based on coordinates so we can find a center point to be the root
    std::sort(parks.begin(), parks.end(), [axis](const NationalPark& a, const NationalPark& b) {
        return (axis == 0) ? a.location.lat < b.location.lat : a.location.lon < b.location.lon;
    });

    // Find the median
    size_t medianIndex = parks.size() / 2;
    
    // Create a new node with the median element
    std::string id = std::to_string(nodeCount++);
    KDTNode* node = new KDTNode(parks[medianIndex], id);

    // Recursively build left and right subtrees
    std::vector<NationalPark> leftParks(parks.begin(), parks.begin() + medianIndex);
    std::vector<NationalPark> rightParks(parks.begin() + medianIndex + 1, parks.end());

    node->left = buildTree(leftParks, depth + 1);
    node->right = buildTree(rightParks, depth + 1);

    return node;
}

// Destroys Specific node
void KDTree::destroy(KDTNode* node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

// Finds nearest coordinate
NationalPark KDTree::findNearest(const Point& target) {
    double bestDist;
    NationalPark best;

    if (!root) { 
        return NationalPark();
    }

    path.clear();
    bestDist = std::numeric_limits<double>::max();
    std::unordered_set<int> visited;

    findNearestHelper(root, target, best, bestDist, 0, visited);
    
    return best;
}

void KDTree::findNearestHelper(KDTNode* node, const Point& target, NationalPark& best, double& bestDist, int depth, std::unordered_set<int>& visited) {
    if (!node) {
        return;
    }

    double dist = distance(node->park.location, target);
    double diff;
    int axis = depth % 2;

    if (dist < bestDist) {
        bestDist = dist;
        best = node->park;
        nearestNodeId = std::stoi(node->id); // Track the nearest node ID
    }

    diff = (axis == 0) ? target.lat - node->park.location.lat : target.lon - node->park.location.lon;

    KDTNode* near = (diff < 0) ? node->left : node->right;
    KDTNode* far = (diff < 0) ? node->right : node->left;

// DOT file helper
    int nodeId = std::stoi(node->id);

    if (near) {
        int nearId = std::stoi(near->id);
        if (visited.find(nearId) == visited.end()) {
            path.insert({nodeId, nearId, "green"});
        }
    }

    if (far) {
        int farId = std::stoi(far->id);
        if (visited.find(farId) == visited.end()) {
            path.insert({nodeId, farId, "black"});
        }
    }

    // Mark this node as visited
    visited.insert(nodeId);

    findNearestHelper(near, target, best, bestDist, depth + 1, visited);

    // Only check far node if it's within the best distance
    if (std::abs(diff) < bestDist) {
        findNearestHelper(far, target, best, bestDist, depth + 1, visited);
    }
}

double KDTree::distance(const Point& a, const Point& b) {
    double dx = a.lat - b.lat;
    double dy = a.lon - b.lon;
    return std::sqrt(dx * dx + dy * dy);
}

// Insert a new data point
void KDTree::insert(const NationalPark& park) {
    root = insertHelper(root, park, 0);
}

KDTNode* KDTree::insertHelper(KDTNode* node, const NationalPark& park, int depth) {
    if (!node) {
        std::string id = std::to_string(nodeCount++);
        return new KDTNode(park, id);
    }

    int axis = depth % 2;

    if ((axis == 0) ? park.location.lat < node->park.location.lat : park.location.lon < node->park.location.lon) {
        node->left = insertHelper(node->left, park, depth + 1);
    } else {
        node->right = insertHelper(node->right, park, depth + 1);
    }

    return node;
}

void KDTree::DOTFile(const std::string& filename) {
    std::ofstream ofs(filename);
    ofs << "digraph G {" << std::endl << std::endl;

    for (const auto& edge : path) {
        if (edge.from != edge.to) {
            std::string color = (edge.from == nearestNodeId || edge.to == nearestNodeId) ? "purple" : edge.label;
            ofs << "    " << edge.from << " -> " << edge.to << " [color=\"" << color << "\"];" << std::endl;
        }
    }

    // Highlight the nearest node
    if (nearestNodeId != -1) {
        ofs << "    " << nearestNodeId << " [color=purple, style=bold];" << std::endl;
    }

    ofs << std::endl << "}" << std::endl;
}