// File Name: Heap.h
// Project: CS 221 Assignment 1 Problem 2
// Author: Gogi Benny
// Date: October 23, 2026
//
// Purpose: Declare the supplied heap adapted to scheduled event pointers.
//
// Major Items:
// - one based heap storage and heap operations
// - Event pointers prioritized by scheduled time

#ifndef HEAP_H
#define HEAP_H

#include <vector>

using namespace std;

class Event;

/**
   This class schedules events with earlier times first.
   Event pointers are not owned by this heap.
*/
class Heap
{
  public:
    /**
       Constructs an empty heap.
    */
    Heap();

    /**
       Adds a new element to this heap.
       @param new_element a non-null pointer to the event to add
    */
    void push(Event* new_element);

    /**
       Gets the earliest event; the heap must not be empty.
       @return a pointer to the earliest event
    */
    Event* top() const;

    /**
       Removes the earliest event pointer; the heap must not be empty.
       The event itself is not deleted.
    */
    void pop();

    /**
       Gets the number of events in this heap.
       @return the number of stored events
    */
    int size() const;

  private:
    /**
       Turns the tree back into a heap, provided only the root
       node violates the heap condition.
    */
    void fix_heap();

    /**
       Returns the index of the left child.
       @param index the index of a node in this heap
       @return the index of the left child of the given node
    */
    int get_left_child_index(int index);

    /**
       Returns the index of the right child.
       @param index the index of a node in this heap
       @return the index of the right child of the given node
    */
    int get_right_child_index(int index);

    /**
       Returns the index of the parent.
       @param index the index of a node in this heap
       @return the index of the parent of the given node
    */
    int get_parent_index(int index);

    /**
       Gets the event pointer of the left child.
       @param index the index of a node in this heap
       @return the event pointer of the left child of the given node
    */
    Event* get_left_child(int index);

    /**
       Gets the event pointer of the right child.
       @param index the index of a node in this heap
       @return the event pointer of the right child of the given node
    */
    Event* get_right_child(int index);

    /**
       Gets the event pointer of the parent.
       @param index the index of a node in this heap
       @return the event pointer of the parent of the given node
    */
    Event* get_parent(int index);

    vector<Event*> elements;
};

#endif
