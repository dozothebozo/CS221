// File Name: treeNode.cpp
// Project: CS221 Assignment 1, Problem 1
// Author: Gogi Benny; adapted from supplied CS221 code
// Date: October 20, 2026
// Purpose: Insert, find, and print values in a tree subtree.
// Major Items: TreeNode member definitions.
#include "treeNode.h"
#include <iostream>
#include <string>
using namespace std;

void TreeNode::insert_node(TreeNode* new_node)
{
    if (new_node->data < data)
    {
        if (left == NULL)
        {
            left = new_node;
            new_node->parent = this;
        }
        else
            left->insert_node(new_node);
    }
    else if (data < new_node->data)
    {
        if (right == NULL)
        {
            right = new_node;
            new_node->parent = this;
        }
        else
            right->insert_node(new_node);
    }
    else
        delete new_node;
}

bool TreeNode::find(string value) const
{
    if (value < data)
    {
        if (left == NULL)
            return false;
        else
            return left->find(value);
    }
    else if (data < value)
    {
        if (right == NULL)
            return false;
        else
            return right->find(value);
    }
    else
        return true;
}

void TreeNode::print_nodes() const
{
    if (left != NULL)
        left->print_nodes();
    cout << data << "\n";
    if (right != NULL)
        right->print_nodes();
}
