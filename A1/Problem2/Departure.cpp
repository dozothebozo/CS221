// File Name: Departure.cpp
// Project: CS 221 Assignment 1 Problem 2
// Author: Gogi Benny
// Date: October 23, 2026
//
// Purpose: Process a customer's departure from the stand.
//
// Major Items:
// - Stool release
// - Departure message

#include "Departure.h"
#include "Simulation.h"

#include <iostream>

using namespace std;

Departure::Departure(double time, Simulation* owner) : Event(time, owner)
{
}

void Departure::act()
{
    simulation->release_seat();
    print_time();
    cout << "Customer finishes eating, leaves.\n";
}
