// File Name: treeIterator.h
// Project: CS221 Assignment 1, Problem 1
// Author: Gogi Benny
// Date: October 20, 2026
// Purpose: Declare an iterator for in-order tree traversal.
// Major Items: TreeIterator class.

#pragma once
#include <string>

class BinarySearchTree;
class TreeNode;

class TreeIterator
{
  public:
    /**
       Constructs an iterator that does not belong to a tree.
    */
    TreeIterator();

    /**
       Gets the current value. The iterator must point to a node.
       @return the current node's value
    */
    std::string get() const;

    /**
       Advances in order. The iterator must point to a node.
    */
    void next();

    /**
       Moves backward in order, including from end on a nonempty tree.
       The iterator must belong to a tree and must not be at begin.
    */
    void previous();

    /**
       Compares the positions and owning trees of two iterators.
       @param other the iterator to compare
       @return true if both iterators represent the same tree position
    */
    bool equals(TreeIterator other) const;

  private:
    TreeNode* position;
    const BinarySearchTree* container;
    friend class BinarySearchTree;
};
