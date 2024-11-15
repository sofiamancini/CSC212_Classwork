#include "bst.h"

// node constructor
BSTNode::BSTNode(int data){
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

// node destructor
BSTNode::~BSTNode(){

}

// tree constructor
BSTree::BSTree(){
    this->root = nullptr;
}

// tree destructor
BSTree::~BSTree(){
    this->destroy();
}

// insert (takes BSTNode* and int and returns BSTNode*)
BSTNode* BSTree::insert(BSTNode* node, int data){
    if(node == nullptr){
        return new BSTNode(data);
    }

    if(data < node->data){
        node->left = this->insert(node->left, data);
    }else if(data > node->data){
        node->right = this->insert(node->right, data);
    }

    return node;
}

void BSTree::insert(int data){
    this->root = this->insert(this->root, data);
}

// height
int BSTree::height(BSTNode* node){
    if (node == nullptr){
        return -1;
    }else{
        int left_height = this->height(node->left);
        int right_height = this->height(node->right);

        return 1+ (left_height > right_height ? left_height : right_height);
    }
}

int BSTree::height(){
    return this->height(this->root);
}

// preorder
void BSTree::preorder(BSTNode* node, std::ostream& os){
    if(node != nullptr){
        os << node->data << " ";
        this->preorder(node->left, os);
        this->preorder(node->right, os);
    }
}

void BSTree::preorder(std::ostream& os){
    this->preorder(this->root, os);
    os << std::endl;
}

// inorder
void BSTree::inorder(BSTNode* node, std::ostream& os){
    if(node != nullptr){
        this->inorder(node->left, os);
        os << node->data << " ";
        this->inorder(node->right, os);
    }
}

void BSTree::inorder(std::ostream& os){
    this->inorder(this->root, os);
    os << std::endl;
}

// postorder
void BSTree::postorder(BSTNode* node, std::ostream& os){
    if(node != nullptr){
        this->postorder(node->left, os);
        this->postorder(node->right, os);
        os << node->data << " ";
    }
}

void BSTree::postorder(std::ostream& os){
    this->postorder(this->root, os);
    os << std::endl;
}

// destroy
void BSTree::destroy(BSTNode* node){
    if(node != nullptr){
        this->destroy(node->left);
        this->destroy(node->right);
        delete node;
    }
}

void BSTree::destroy(){
    this->destroy(this->root);
    this->root = nullptr;
}

// search
bool BSTree::search(int data){
    BSTNode* current = this->root;

    while(current != nullptr){
        if(data == current->data){
            return true;
        }else if(data < current->data){
            current = current->left;
        }else{
            current = current->right;
        }
    }

    return false;
}

// remove
void BSTree::remove(int data){
    this->root = this->remove(this->root, data);
}

BSTNode* BSTree::remove(BSTNode* node, int data){
    if(node == nullptr){
        return nullptr;
    }

    if(data < node->data){
        node->left = this->remove(node->left, data);
    }else if(data > node->data){
        node->right = this->remove(node->right, data);
    }else{
        if(node->left == nullptr){
            BSTNode* temp = node->right;
            delete node;
            return temp;
        }else if(node->right == nullptr){
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }

        BSTNode* temp = node->right;
        while(temp->left != nullptr){
            temp = temp->left;
        }

        node->data = temp->data;
        node->right = this->remove(node->right, temp->data);
    }

    return node;
}




