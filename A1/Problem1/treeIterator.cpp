// File Name: treeIterator.cpp
// Project: CS221 Assignment 1, Problem 1
// Author: Gogi Benny
// Date: October 20, 2026
// Purpose: Move through a tree using its child and parent links.
// Major Items: TreeIterator member definitions.

#include "treeIterator.h"
#include "bintree.h"
#include <cassert>

TreeIterator::TreeIterator()
{
    position = NULL;
    container = NULL;
}

std::string TreeIterator::get() const
{
    assert(position != NULL);
    return position->data;
}

void TreeIterator::next()
{
    assert(position != NULL);
    if (position->right != NULL)
    {
        position = position->right;
        while (position->left != NULL)
            position = position->left;
    }
    else
    {
        TreeNode* child = position;
        TreeNode* parent = position->parent;
        while (parent != NULL && child == parent->right)
        {
            child = parent;
            parent = parent->parent;
        }
        position = parent;
    }
}

void TreeIterator::previous()
{
    assert(container != NULL);
    if (position == NULL)
    {
        position = container->root;
        assert(position != NULL);
        while (position->right != NULL)
            position = position->right;
    }
    else if (position->left != NULL)
    {
        position = position->left;
        while (position->right != NULL)
            position = position->right;
    }
    else
    {
        TreeNode* child = position;
        TreeNode* parent = position->parent;
        while (parent != NULL && child == parent->left)
        {
            child = parent;
            parent = parent->parent;
        }
        assert(parent != NULL);
        position = parent;
    }
}

bool TreeIterator::equals(TreeIterator other) const
{
    return position == other.position && container == other.container;
}
