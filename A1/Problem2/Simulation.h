// File Name: Simulation.h
// Project: CS 221 Assignment 1 Problem 2
// Author: Gogi Benny
// Date: October 24, 2026
//
// Purpose: Declare the hot dog stand simulation and its event storage.
//
// Major Items:
// - Seat counts and customer totals
// - Owned event pointers and the scheduling heap
// - Simulation execution and event scheduling

#ifndef SIMULATION_H
#define SIMULATION_H

#include "Heap.h"

#include <vector>

class Event;

class Simulation
{
  public:
    /**
       Constructs a stand and its initial arrival events.
       @param seat_count the number of stools, which must not be negative
       @param arrival_count the number of arrivals, which must not be negative
    */
    Simulation(int seat_count, int arrival_count);

    /**
       Deletes the initial and generated events owned by this simulation.
    */
    ~Simulation();

    /**
       Prevents copying the simulation's owned event pointers.
       @param other the simulation that cannot be copied
    */
    Simulation(const Simulation& other) = delete;

    /**
       Prevents assigning the simulation's owned event pointers.
       @param other the simulation that cannot be copied
       @return no value because assignment is disabled
    */
    Simulation& operator=(const Simulation& other) = delete;

    /**
       Processes the events in time order and prints a summary; call once.
    */
    void run();

    /**
       Takes an available stool and updates the customer totals.
       @return true if the customer was seated, false if the stand was full
    */
    bool seat_customer();

    /**
       Frees one occupied stool; at least one stool must be occupied.
    */
    void release_seat();

    /**
       Takes ownership of an event and adds it to the scheduling heap.
       @param new_event a newly allocated event belonging to this simulation
    */
    void schedule(Event* new_event);

    /**
       Gets the number of customers who were seated.
       @return the number of seated customers
    */
    int get_served() const;

    /**
       Gets the number of customers who could not find a seat.
       @return the number of customers turned away
    */
    int get_lost() const;

    /**
       Gets the largest number of stools occupied at one time.
       @return the peak number of occupied stools
    */
    int get_peak() const;

  private:
    int seats;
    int occupied_seats;
    int served_customers;
    int lost_customers;
    int peak_occupied;

    // This vector owns the events; the heap only stores pointers to them.
    std::vector<Event*> events;
    Heap event_heap;
};

#endif
