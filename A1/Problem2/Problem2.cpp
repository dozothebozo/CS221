// File Name: Problem2.cpp
// Project: CS 221 Assignment 1 Problem 2
// Author: Gogi Benny
// Date: October 22, 2026
//
// Purpose: Compare three stool counts for a stand with ten arriving customers.
//
// Major Items:
// - Ten arrivals four minutes apart, starting at 5:00
// - Random stays of 17 to 19 minutes
// - Six, four, and five stools compared using the same random seed

#include "Simulation.h"

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

/**
   Runs one demonstration with a chosen number of stools.
   @param seats the number of stools
   @param description the reason for testing this stool count
*/
void testSimulation(int seats, const string& description);

// Demonstration settings for the required three runs.
const int ARRIVAL_COUNT = 10;
const unsigned int RANDOM_SEED = 221;
const int HIGH_STOOL_COUNT = 6;
const int LOW_STOOL_COUNT = 4;
const int SUITABLE_STOOL_COUNT = 5;

/**
   Compares slightly high, slightly low, and suitable stool counts.
   @return zero after the demonstrations finish
*/
int main()
{
    cout << "Hot Dog Stand Simulation\n";
    cout << "Ten arrivals, four minutes apart; random stays of 17 to 19 minutes.\n";
    cout << "The same seed is used for each run so the results can be repeated.\n\n";

    testSimulation(HIGH_STOOL_COUNT, "Slightly more stools than needed");
    testSimulation(LOW_STOOL_COUNT, "Slightly fewer stools than needed");
    testSimulation(SUITABLE_STOOL_COUNT, "Suitable number of stools");

    cout << "Five stools serve all ten arrivals without an unused extra stool\n";
    cout << "at peak occupancy for this workload.\n";
    return 0;
}

void testSimulation(int seats, const string& description)
{
    cout << description << ": " << seats << " stools\n";
    srand(RANDOM_SEED);

    Simulation stand(seats, ARRIVAL_COUNT);
    stand.run();
}
