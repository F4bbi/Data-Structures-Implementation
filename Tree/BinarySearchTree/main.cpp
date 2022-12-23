#include <iostream>

#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    BinarySearchTree<int> bst;
    bst.insertIterative(11);
    bst.insertIterative(4);
    bst.insertRecursive(9);
    bst.insertRecursive(6);
    bst.insertIterative(1);
    bst.insertIterative(10);
    bst.insertRecursive(7);
    bst.insertIterative(8);
    bst.print();
    return 0;
}
