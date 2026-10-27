// File Name: Event.cpp
// Project: CS 221 Assignment 1 Problem 2
// Author: Gogi Benny
// Date: October 23, 2026
//
// Purpose: Store an event time and provide common event behavior.
//
// Major Items:
// - Event construction and destruction
// - Scheduled time access and output

#include "Event.h"

#include <cassert>
#include <iomanip>
#include <iostream>

using namespace std;

Event::Event(double time, Simulation* owner) : simulation(owner), event_time(time)
{
    assert(time >= 0 && owner != nullptr);
}

Event::~Event()
{
}

double Event::get_time() const
{
    return event_time;
}

void Event::act()
{
}

void Event::print_time() const
{
    int minutes = static_cast<int>(event_time);

    cout << "Time " << minutes / 60 << ':' << setfill('0') << setw(2) << minutes % 60
         << setfill(' ') << ". ";
}
