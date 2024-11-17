#pragma once
#include <memory>
#include <sstream>
#include <unordered_map>

#include "../Threading/IETThread.h"
#include "../Process/Process.h"
#include "../TypeDefRepo.h"

//
static const String FCFS_SCHEDULER_NAME = "FCFSScheduler"; // FCFS scheduler name
static const String RR_SCHEDULER_NAME = "RRScheduler";     // RR scheduler name
//

class AScheduler : public IETThread
{
public:
	enum SchedulingAlgorithm {
		FCFS,
		ROUND_ROBIN
	};

	AScheduler(SchedulingAlgorithm schedulingAlgo, int pid, String processName);

	void addProcess(std::shared_ptr<Process> process);
	std::shared_ptr<Process> findProcess(String processName);
	void run() override;
	void stop();

	virtual void init() = 0;
	virtual void execute() = 0;

	struct ProcessInfo {
		int pid;
		String name;
		int cpuID;
		int lineCounter;
		int linesOfCode;
		int remainingTime;
	};

	std::vector<std::shared_ptr<Process>> getProcessesInOrder() const;


protected:
	SchedulingAlgorithm algo;
	ProcessInfo processInfo;

	std::unordered_map<std::string, std::shared_ptr<Process>> readyQueueMap; // Fast lookup by name
	std::vector<std::shared_ptr<Process>> readyQueueOrder; // Maintains insertion order
	bool isRunning;
};

