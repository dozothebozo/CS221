// File Name: Heap.cpp
// Project: CS 221 Assignment 1 Problem 2
// Author: Gogi Benny
// Date: October 23, 2026
//
// Purpose: Adapt the supplied heap to process earlier events first.
//
// Major Items:
// - one based heap storage and heap operations
// - Event pointers prioritized by scheduled time

#include "Heap.h"
#include "Event.h"

#include <cassert>

Heap::Heap()
{
    elements.push_back(0);
}

void Heap::push(Event* new_element)
{
    assert(new_element != nullptr);

    // Add a new leaf
    elements.push_back(0);
    int index = static_cast<int>(elements.size()) - 1;

    // Demote parents scheduled later than the new event
    while (index > 1 && get_parent(index)->get_time() > new_element->get_time())
    {
        elements[index] = get_parent(index);
        index = get_parent_index(index);
    }

    // Store the new element into the vacant slot
    elements[index] = new_element;
}

Event* Heap::top() const
{
    assert(size() > 0);
    return elements[1];
}

void Heap::pop()
{
    assert(size() > 0);

    // Remove last element
    int last_index = static_cast<int>(elements.size()) - 1;
    Event* last = elements[last_index];
    elements.pop_back();

    if (last_index > 1)
    {
        elements[1] = last;
        fix_heap();
    }
}

int Heap::size() const
{
    return static_cast<int>(elements.size()) - 1;
}

void Heap::fix_heap()
{
    Event* root = elements[1];

    int last_index = static_cast<int>(elements.size()) - 1;
    // Promote children scheduled earlier than the last event

    int index = 1;
    bool more = true;
    while (more)
    {
        int child_index = get_left_child_index(index);
        if (child_index <= last_index)
        {
            // Get earlier child

            // Get left child first
            Event* child = get_left_child(index);

            // Use right child instead if it is earlier
            if (get_right_child_index(index) <= last_index &&
                get_right_child(index)->get_time() < child->get_time())
            {
                child_index = get_right_child_index(index);
                child = get_right_child(index);
            }

            // Check if the earlier child is scheduled before root
            if (child->get_time() < root->get_time())
            {
                // Promote child
                elements[index] = child;
                index = child_index;
            }
            else
            {
                // Root is scheduled no later than either child
                more = false;
            }
        }
        else
        {
            // No children
            more = false;
        }
    }

    // Store root element in vacant slot
    elements[index] = root;
}

int Heap::get_left_child_index(int index)
{
    return 2 * index;
}

int Heap::get_right_child_index(int index)
{
    return 2 * index + 1;
}

int Heap::get_parent_index(int index)
{
    return index / 2;
}

Event* Heap::get_left_child(int index)
{
    return elements[2 * index];
}

Event* Heap::get_right_child(int index)
{
    return elements[2 * index + 1];
}

Event* Heap::get_parent(int index)
{
    return elements[index / 2];
}
