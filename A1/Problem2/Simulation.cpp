// File Name: Simulation.cpp
// Project: CS 221 Assignment 1 Problem 2
// Author: Gogi Benny
// Date: October 24, 2026
//
// Purpose: Run the hot dog stand simulation using the supplied heap algorithm.
//
// Major Items:
// - Initial arrival creation and event cleanup
// - Chronological event processing
// - Seating, departure scheduling, and customer totals

#include "Simulation.h"
#include "Arrival.h"
#include "Event.h"

#include <cassert>
#include <iostream>

using namespace std;

// Arrival times are minutes after midnight, starting at 5:00.
const int START_TIME = 5 * 60;
const int ARRIVAL_INTERVAL = 4;

Simulation::Simulation(int seat_count, int arrival_count)
    : seats(seat_count)
    , occupied_seats(0)
    , served_customers(0)
    , lost_customers(0)
    , peak_occupied(0)
{
    assert(seat_count >= 0 && arrival_count >= 0);

    for (int index = 0; index < arrival_count; index++)
    {
        events.push_back(new Arrival(START_TIME + index * ARRIVAL_INTERVAL, this));
    }
}

Simulation::~Simulation()
{
    for (int index = 0; index < static_cast<int>(events.size()); index++)
    {
        delete events[index];
    }
}

void Simulation::run()
{
    for (int index = 0; index < static_cast<int>(events.size()); index++)
    {
        event_heap.push(events[index]);
    }

    while (event_heap.size() > 0)
    {
        Event* current = event_heap.top();
        event_heap.pop();
        current->act();
    }

    cout << "\nCustomers seated: " << served_customers << '\n';
    cout << "Customers turned away: " << lost_customers << '\n';
    cout << "Peak stools occupied: " << peak_occupied << " of " << seats << "\n\n";
}

bool Simulation::seat_customer()
{
    if (occupied_seats == seats)
    {
        lost_customers++;
        return false;
    }

    occupied_seats++;
    served_customers++;

    if (occupied_seats > peak_occupied)
    {
        peak_occupied = occupied_seats;
    }

    return true;
}

void Simulation::release_seat()
{
    assert(occupied_seats > 0);
    occupied_seats--;
}

void Simulation::schedule(Event* new_event)
{
    assert(new_event != nullptr);
    events.push_back(new_event);
    event_heap.push(new_event);
}

int Simulation::get_served() const
{
    return served_customers;
}

int Simulation::get_lost() const
{
    return lost_customers;
}

int Simulation::get_peak() const
{
    return peak_occupied;
}
