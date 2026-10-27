// File Name: bintree.h
// Project: CS221 Assignment 1, Problem 1
// Author: Gogi Benny
// Date: October 20, 2026
// Purpose: Declare a binary search tree with in-order iterators.
// Major Items: BinarySearchTree class.
#pragma once
#include "treeIterator.h"
#include "treeNode.h"
#include <iostream>
#include <string>
using namespace std;

class BinarySearchTree
{
  public:
    /**
       Constructs an empty tree.
    */
    BinarySearchTree();

    /**
       Deletes all nodes owned by this tree.
    */
    ~BinarySearchTree();

    /**
       Prevents copying a tree's owned node pointers.
       @param other the tree that cannot be copied
    */
    BinarySearchTree(const BinarySearchTree& other) = delete;

    /**
       Prevents assigning a tree's owned node pointers.
       @param other the tree that cannot be assigned
       @return assignment is disabled
    */
    BinarySearchTree& operator=(const BinarySearchTree& other) = delete;

    /**
       Inserts a value if it is not already in the tree.
       @param data the value to insert
    */
    void insert(string data);

    /**
       Removes a value if it is present. Reacquire iterators after erasing.
       @param data the value to remove
    */
    void erase(string data);

    /**
       Counts occurrences of a value in this tree.
       @param data the value to find
       @return 1 if the value is present, otherwise 0
    */
    int count(string data) const;

    /**
       Prints the values in order.
    */
    void print() const;

    /**
       Gets the iterator at the first value.
       @return an iterator at the smallest value, or end for an empty tree
    */
    TreeIterator begin() const;

    /**
       Gets the position past the last value.
       @return an iterator past the largest value
    */
    TreeIterator end() const;

  private:
    /**
       Deletes a node and all of its descendants.
       @param node the root of the subtree to delete
    */
    void clear(TreeNode* node);

    TreeNode* root;
    friend class TreeIterator;
};
