// File Name: treeNode.h
// Project: CS221 Assignment 1, Problem 1
// Author: Gogi Benny; adapted from supplied CS221 code
// Date: October 20, 2026
// Purpose: Declare a tree node with child and parent links.
// Major Items: TreeNode class.

#pragma once
#include <iostream>
#include <string>

using namespace std;

class TreeNode
{
  public:
    /**
       Inserts an allocated node into this subtree, deleting it if duplicated.
       @param new_node the node whose ownership is transferred to this subtree
    */
    void insert_node(TreeNode* new_node);

    /**
       Prints this subtree in order.
    */
    void print_nodes() const;

    /**
       Finds a value in this subtree.
       @param value the value to find
       @return true if the value is present, otherwise false
    */
    bool find(string value) const;

  private:
    string data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    friend class BinarySearchTree;
    friend class TreeIterator;
};
