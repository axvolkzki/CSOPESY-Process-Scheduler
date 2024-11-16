#pragma once
#include "../TypedefRepo.h"
#include "../Command/PrintCommand.h"

#include <memory>
#include <vector>



class Process
{
public:
    enum ProcessState {
        READY,
        RUNNING,
        WAITING,
        FINISHED
    };

    Process(int pid, String name);

    void addCommand(ICommand::CommandType commandType);
    void executeCurrentCommand() const;
    void moveToNextLine();

    bool isFinished() const;
    int getRemainingTime() const;
    int getCommandCounter() const;
    int getLinesOfCode() const;
    int getPID() const;
    int getCPUCoreID() const;
    ProcessState getState() const;
    String getName() const;

    std::tm getArrivalTime() const;
    String getFormattedArrivalTime() const;

    void generateArrivalTime();

private:
    int pid;
    String name;
    int commandCounter = 0;
    std::tm localArrivalTime; // Store the Arrival Time

    typedef std::vector<std::shared_ptr<ICommand>> CommandList;
    CommandList commandList;
    int cpuCoreID = -1;
    ProcessState currentState;

    friend class ResourceEmulator;
};


