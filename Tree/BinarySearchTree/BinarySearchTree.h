#pragma once

#include <iostream> 

template<class T>    
class BinarySearchTree {
    class Node {
        public:
            T key;
            Node* left;
            Node* right;
            
            // default constructor
            Node() = default;
            // constructor with data
            Node(const T& value) : key(value), left(NULL), right(NULL) {}
    };
    protected:
        Node* root;
    private:
        void preOrderHelper(Node*& treeNode);
        void inOrderHelper(Node*& treeNode);
        void postOrderHelper(Node*& treeNode);
        bool searchRecursiveHelper(Node*& treeNode, T key);
        void insertRecursiveHelper(Node*& treeNode, T key);
        int getHeight(Node*& treeNode);
        Node* minNode(Node*& treeNode);
        Node* maxNode(Node*& treeNode);
        Node* removeRecursiveHelper(Node*& root, T key);
        Node* getParent(Node*& root, T key, Node*& parent);
        void unlink(Node*& p, Node*& u);
        void printHelper(Node* root, int space);
        void clearHelper(Node*& root);
        void printLevel(Node* root, int level);
    public:
        BinarySearchTree() : root(NULL) {}
        BinarySearchTree(const BinarySearchTree& copyBST);
        ~BinarySearchTree();
        void initRandom(int n);
        bool searchIterative(T key);
        bool searchRecursive(T key);
        void insertIterative(T key);
        void insertRecursive(T key);
        void preOrder();
        void inOrder();
        void postOrder();
        void levelOrderIterative();
        void levelOrderRecursive();
        T min();
        T max();
        void removeIterative(T key);
        void removeRecursive(T key);
        int getHeight();
        void clear();
        void print();
};