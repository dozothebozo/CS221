// File Name: Arrival.cpp
// Project: CS 221 Assignment 1 Problem 2
// Author: Gogi Benny
// Date: October 23, 2026
//
// Purpose: Process customer arrivals and schedule seated customers' departures.
//
// Major Items:
// - Seat availability check
// - Random stay duration and departure event
// - Arrival messages

#include "Arrival.h"
#include "Departure.h"
#include "Simulation.h"

#include <cstdlib>
#include <iostream>

using namespace std;

// bounds for the demonstration, measured in minutes.
const int MIN_STAY = 17;
const int MAX_STAY = 19;

Arrival::Arrival(double time, Simulation* owner) : Event(time, owner)
{
}

void Arrival::act()
{
    print_time();

    if (simulation->seat_customer())
    {
        cout << "Customer is seated.\n";

        int duration = MIN_STAY + rand() % (MAX_STAY - MIN_STAY + 1);
        simulation->schedule(new Departure(get_time() + duration, simulation));
    }
    else
    {
        cout << "Customer is unable to find a seat, leaves.\n";
    }
}
