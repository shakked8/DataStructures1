#include <iostream>
#include <cassert>
#include "AVLTree.h"


void testInsertAndSearch() {
    AVLTree<int> tree;
    tree.insert(new Node<int>(5, nullptr));
    tree.insert(new Node<int>(3, nullptr));
    tree.insert(new Node<int>(7, nullptr));

    assert(tree.isNodeInTree(5) == true);
    assert(tree.isNodeInTree(3) == true);
    assert(tree.isNodeInTree(7) == true);

    // Checking for a value that doesn't exist
    assert(tree.isNodeInTree(10) == false);

    std::cout << "Insertion and Search tests passed.\n";
}

void testDeletion() {
    AVLTree<int> tree;
    tree.insert(new Node<int>(5, nullptr));
    tree.insert(new Node<int>(3, nullptr));
    tree.insert(new Node<int>(7, nullptr));

    tree.deleteNode(3);
    assert(tree.isNodeInTree(3) == false);

    tree.deleteNode(7);
    assert(tree.isNodeInTree(7) == false);

    tree.deleteNode(5);
    assert(tree.isNodeInTree(5) == false);

    std::cout << "Deletion tests passed.\n";
}

int main() {
    testInsertAndSearch();
    testDeletion();

    return 0;
}
