#include "AScheduler.h"

AScheduler::AScheduler(SchedulingAlgorithm schedulingAlgo, int pid, String processName)
{
	this->algo = schedulingAlgo;
	this->isRunning = true;
}

void AScheduler::addProcess(std::shared_ptr<Process> process)
{
	this->readyQueueMap[process->getName()] = process;		// for fast lookup by name

	this->readyQueueOrder.push_back(process);				// vector for readyQueue
}

std::shared_ptr<Process> AScheduler::findProcess(String processName)
{
	auto it = this->readyQueueMap.find(processName);

	if (it != this->readyQueueMap.end()) {
		return it->second;	// Return the shared_ptr to the found process
	}
	return nullptr; // Process not found

}



void AScheduler::run()
{
	
}

void AScheduler::stop()
{
	this->isRunning = false;
}

std::vector<std::shared_ptr<Process>> AScheduler::getProcessesInOrder() const
{
	return this->readyQueueOrder;
}
