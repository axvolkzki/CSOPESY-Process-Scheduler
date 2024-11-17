#pragma once
#include <map>
#include <memory>


#include "../TypeDefRepo.h"
#include "../Process/Process.h"
#include "../Console/ConsoleManager.h"
#include "AScheduler.h"

class GlobalScheduler
{
public:
	static GlobalScheduler* getInstance();
	static void initialize();
	static void destroy();
	
	void tick() const;

	std::shared_ptr<Process> createUniqueProcess(String name, int totalLines);
	std::shared_ptr<Process> findProcess(String name) const;

private:
	GlobalScheduler();
	~GlobalScheduler() = default;
	GlobalScheduler(GlobalScheduler const&) {};
	GlobalScheduler& operator=(GlobalScheduler const&) {};
	static GlobalScheduler* sharedInstance;

	int pidCounter;
	std::shared_ptr<AScheduler> scheduler;

	std::shared_ptr<Process> findProcess(String processName);
	String generateUniqueProcessName(int id);
};

