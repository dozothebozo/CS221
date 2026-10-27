// File Name: Departure.h
// Project: CS 221 Assignment 1 Problem 2
// Author: Gogi Benny
// Date: October 23, 2026
//
// Purpose: Declare a departure that frees an occupied stool.
//
// Major Items:
// - Departure construction
// - Departure action

#ifndef DEPARTURE_H
#define DEPARTURE_H

#include "Event.h"

class Departure : public Event
{
  public:
    /**
       Constructs a customer departure.
       @param time the departure time in minutes after midnight
       @param owner the simulation that owns this event
    */
    Departure(double time, Simulation* owner);

    /**
       Frees the customer's stool and prints the departure message.
    */
    void act() override;
};

#endif
