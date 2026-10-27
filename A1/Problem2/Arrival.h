// File Name: Arrival.h
// Project: CS 221 Assignment 1 Problem 2
// Author: Gogi Benny
// Date: October 23, 2026
//
// Purpose: Declare a customer arrival event.
//
// Major Items:
// - Arrival construction
// - Seating and departure scheduling

#ifndef ARRIVAL_H
#define ARRIVAL_H

#include "Event.h"

class Arrival : public Event
{
  public:
    /**
       Constructs a customer arrival.
       @param time the arrival time in minutes after midnight
       @param owner the simulation that owns this event
    */
    Arrival(double time, Simulation* owner);

    /**
       Seats the customer if possible and schedules a departure.
    */
    void act() override;
};

#endif
