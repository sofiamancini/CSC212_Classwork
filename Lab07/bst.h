#pragma once
#include <iostream>
#include <queue>
#include <stack>

class BSTNode;

class BSTree{
    private:
        BSTNode* root;
        BSTNode* insert(BSTNode* node, int data);
        int height(BSTNode* node);
        void preorder(BSTNode* node, std::ostream& os);
        void inorder(BSTNode* node, std::ostream& os);
        void postorder(BSTNode* node, std::ostream& os);
        void destroy(BSTNode* node);
        BSTNode* remove(BSTNode* node, int data);

    public:
        BSTree();
        ~BSTree();

        void insert(int data);
        int height();
        void preorder(std::ostream& os = std::cout);
        void inorder(std::ostream& os = std::cout);
        void postorder(std::ostream& os = std::cout);
        void destroy();
        bool search(int data);
        void remove(int data);
};

class BSTNode{
    private:
        int data;
        BSTNode* left;
        BSTNode* right;

        friend class BSTree;

    public:
        BSTNode(int data);
        ~BSTNode();
};