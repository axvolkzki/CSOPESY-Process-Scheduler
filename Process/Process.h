#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

#include "../TypedefRepo.h"

class Process
{
public:
    Process(String name, int totalLines);

    int getCommandCounter() const;
    int getLinesOfCode() const;
    String getName() const;

    std::tm getArrivalTime() const;
    String getFormattedArrivalTime() const;

    void generateArrivalTime();

private:
    void updateArrivalTime(); // Encapsulate logic for setting the arrival time

    int pid;
    String name;
    int commandCounter = 0;
    std::tm localArrivalTime; // Store the Arrival Time
    int totalLines;
};
