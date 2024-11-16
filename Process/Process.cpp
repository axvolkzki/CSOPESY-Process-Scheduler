#include "Process.h"

Process::Process(String name, int totalLines)
    : name(name), totalLines(totalLines)
{
    updateArrivalTime();
}

int Process::getCommandCounter() const
{
    return commandCounter;
}

int Process::getLinesOfCode() const
{
    return totalLines;
}

String Process::getName() const
{
    return name;
}

std::tm Process::getArrivalTime() const
{
    return localArrivalTime;
}

String Process::getFormattedArrivalTime() const
{
    char buffer[64]; // Buffer for formatted time
    std::strftime(buffer, sizeof(buffer), "%m/%d/%Y, %I:%M:%S %p", &localArrivalTime);
    return String(buffer);
}

void Process::generateArrivalTime()
{
    updateArrivalTime();
}

void Process::updateArrivalTime()
{
    auto now = std::chrono::system_clock::now();
    auto currentTime = std::chrono::system_clock::to_time_t(now);
    localtime_s(&localArrivalTime, &currentTime); // Store the arrival time
}
