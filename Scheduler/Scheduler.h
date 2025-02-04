#pragma once
#include <memory>
#include <queue>
#include <thread>
#include <mutex>

#include "../TypeDefRepo.h"
#include "CPUCore.h"
#include "../Process/Process.h"
#include "../Config/GlobalConfig.h"
#include "../Console/ConsoleManager.h"


class Scheduler
{
public:
	static Scheduler* getInstance();
	static void initialize();
	static void destroy();

	void stopScheduler();

	void startSchedulerThread(String scheduler, int delay, int quantum);

	std::shared_ptr<Process> createUniqueProcess();
	std::shared_ptr<Process> findProcess(String name) const;

	void displaySchedulerStatus();


private:
	Scheduler();
	~Scheduler() = default;
	Scheduler(Scheduler const&) {};
	Scheduler& operator=(Scheduler const&) {};
	static Scheduler* sharedInstance;

	int numCPU;
	int bacthProcessFrequency;
	int minInstructions;
	int maxInstructions;

	bool isRunning = false;

	std::queue<std::shared_ptr<Process>> readyQueue;
	std::vector<std::shared_ptr<CPUCore>> cpuCoreList;
	std::vector<std::shared_ptr<Process>> processList;

	std::thread schedulerThread;
	std::mutex schedulerMutex;

	String generateUniqueProcessName(int id);
	void addProcessToReadyQueue(std::shared_ptr<Process> process);

	void runFCFSScheduler(int delay);
	void runRoundRobinScheduler(int delay, int quantum);
};

