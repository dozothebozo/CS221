// File Name: Event.h
// Project: CS 221 Assignment 1 Problem 2
// Author: Gogi Benny
// Date: October 23, 2026
//
// Purpose: Declare the base class for scheduled simulation events.
//
// Major Items:
// - Event time and access to the simulation
// - Virtual action and destructor
// - Event time output

#ifndef EVENT_H
#define EVENT_H

class Simulation;

class Event
{
  public:
    /**
       Constructs an event at a given time.
       @param time the event time in minutes after midnight
       @param owner the simulation that owns this event
    */
    Event(double time, Simulation* owner);

    /**
       Destroys an event through a base class pointer.
    */
    virtual ~Event();

    /**
       Gets the scheduled event time.
       @return the event time in minutes after midnight
    */
    double get_time() const;

    /**
       Performs the event action; a general event does nothing.
    */
    virtual void act();

  protected:
    /**
       Prints the event time in hours and minutes.
    */
    void print_time() const;

    Simulation* simulation;

  private:
    double event_time;
};

#endif
