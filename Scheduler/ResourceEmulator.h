#pragma once
#include "../Config/GlobalConfig.h"
#include "../Threading/SchedulerWorker.h"

#include <vector>
#include <memory>

class ResourceEmulator
{
public:
	static ResourceEmulator* getInstance() {
		if (instance == nullptr) {
			instance = new ResourceEmulator();
		}
		return instance;
	}

	static void initialize();			// Initialize the resource emulator
	static void startAllCPUs();			// Start all CPUs (SchedulerWorker threads)
	static void stopAllCPUs();			// Stop all CPUs (SchedulerWorker threads)
	static void destroy();				// Destroy the resource emulator; cleans ip resources

private:
	std::vector<std::shared_ptr<SchedulerWorker>> cpuCores;	// a list of CPU cores (SchedulerWorkers)
	static ResourceEmulator* instance;						// Singleton instance
};
