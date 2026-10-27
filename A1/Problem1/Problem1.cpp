// File Name: Problem1.cpp
// Project: CS221 Assignment 1, Problem 1
// Author: Gogi Benny; based on supplied bintreeTest.cpp
// Date: October 20, 2026
// Purpose: Test parent links and in-order tree traversal.
// Major Items: main and tree test functions.
//
#include "bintree.h"
#include <iostream>
#include <string>
using namespace std;

/**
   Collects the tree values in forward order.
   @param tree the tree to traverse
   @return the values separated by spaces
*/
string forward_values(const BinarySearchTree& tree);

/**
   Collects the tree values in backward order, starting at end.
   @param tree the tree to traverse
   @return the values separated by spaces
*/
string backward_values(const BinarySearchTree& tree);

/**
   Checks both traversal directions and prints their results.
   @param tree the tree to check
   @param label the test description
   @param expected_forward the expected forward values
   @param expected_backward the expected backward values
   @return true if both traversals match their expected values
*/
bool check_tree(const BinarySearchTree& tree, string label, string expected_forward,
                string expected_backward);

/**
   Tests the supplied tree values and the four supplied erasure cases.
   @return true if all checks pass
*/
bool test_supplied_tree();

/**
   Tests empty trees, duplicates, missing values, and root replacements.
   @return true if all checks pass
*/
bool test_boundaries();

/**
   Tests successor nodes that have right children during erasure.
   @return true if both successor cases pass
*/
bool test_successors();

/**
   Runs the tree tests.
   @return 0 if all checks pass, otherwise 1
*/
int main()
{
    bool supplied_passed = test_supplied_tree();
    bool boundaries_passed = test_boundaries();
    bool successors_passed = test_successors();
    bool passed = supplied_passed && boundaries_passed && successors_passed;

    cout << "\nAll tests: " << (passed ? "PASS" : "FAIL") << endl;
    return passed ? 0 : 1;
}

string forward_values(const BinarySearchTree& tree)
{
    string values;
    TreeIterator iterator = tree.begin();
    while (!iterator.equals(tree.end()))
    {
        if (!values.empty())
            values += " ";
        values += iterator.get();
        iterator.next();
    }
    return values;
}

string backward_values(const BinarySearchTree& tree)
{
    string values;
    TreeIterator iterator = tree.end();
    while (!iterator.equals(tree.begin()))
    {
        iterator.previous();
        if (!values.empty())
            values += " ";
        values += iterator.get();
    }
    return values;
}

bool check_tree(const BinarySearchTree& tree, string label, string expected_forward,
                string expected_backward)
{
    string forward = forward_values(tree);
    string backward = backward_values(tree);
    bool passed = forward == expected_forward && backward == expected_backward;
    cout << "\n" << label << ": " << (passed ? "PASS" : "FAIL") << "\n";
    cout << "Forward:  " << forward << "\n";
    cout << "Backward: " << backward << "\n";
    if (!passed)
    {
        cout << "Expected forward:  " << expected_forward << "\n";
        cout << "Expected backward: " << expected_backward << "\n";
    }
    return passed;
}

bool test_supplied_tree()
{
    BinarySearchTree tree;
    tree.insert("D");
    tree.insert("B");
    tree.insert("A");
    tree.insert("C");
    tree.insert("F");
    tree.insert("E");
    tree.insert("I");
    tree.insert("G");
    tree.insert("H");
    tree.insert("J");
    bool passed = check_tree(tree, "Supplied tree", "A B C D E F G H I J", "J I H G F E D C B A");

    tree.erase("A"); // Removing leaf
    passed = check_tree(tree, "Removing leaf A", "B C D E F G H I J", "J I H G F E D C B") && passed;
    tree.erase("B"); // Removing element with one child
    passed =
        check_tree(tree, "Removing one-child node B", "C D E F G H I J", "J I H G F E D C") && passed;
    tree.erase("F"); // Removing element with two children
    passed = check_tree(tree, "Removing two-child node F", "C D E G H I J", "J I H G E D C") && passed;
    tree.erase("D"); // Removing root
    passed = check_tree(tree, "Removing root D", "C E G H I J", "J I H G E C") && passed;

    bool counts_passed = tree.count("E") == 1 && tree.count("F") == 0;
    cout << "Present E and absent F counts: " << (counts_passed ? "PASS" : "FAIL") << "\n";
    return passed && counts_passed;
}

bool test_boundaries()
{
    BinarySearchTree tree;
    BinarySearchTree other_tree;
    tree.erase("missing");
    bool passed = check_tree(tree, "Empty tree and missing erase", "", "");
    bool equality_passed = tree.begin().equals(tree.end()) && !tree.end().equals(other_tree.end());
    cout << "Empty and different-tree iterators: " << (equality_passed ? "PASS" : "FAIL") << "\n";
    passed = equality_passed && passed;

    tree.insert("B");
    tree.insert("B");
    passed = check_tree(tree, "Single value and duplicate B", "B", "B") && passed;
    passed = tree.count("B") == 1 && tree.count("missing") == 0 && passed;
    tree.erase("B");
    passed = check_tree(tree, "Removing the only node", "", "") && passed;

    tree.insert("B");
    tree.insert("A");
    tree.erase("B");
    passed = check_tree(tree, "Root replaced by left child", "A", "A") && passed;
    tree.insert("C");
    tree.erase("A");
    passed = check_tree(tree, "Root replaced by right child", "C", "C") && passed;
    tree.erase("missing");
    return check_tree(tree, "Missing value leaves tree unchanged", "C", "C") && passed;
}

bool test_successors()
{
    BinarySearchTree deep_successor;
    deep_successor.insert("D");
    deep_successor.insert("B");
    deep_successor.insert("H");
    deep_successor.insert("F");
    deep_successor.insert("G");
    deep_successor.insert("I");
    deep_successor.erase("D");
    bool passed =
        check_tree(deep_successor, "Deep successor with a right child", "B F G H I", "I H G F B");

    BinarySearchTree direct_successor;
    direct_successor.insert("D");
    direct_successor.insert("B");
    direct_successor.insert("F");
    direct_successor.insert("G");
    direct_successor.erase("D");
    return check_tree(direct_successor, "Direct successor with a right child", "B F G", "G F B") &&
           passed;
}
