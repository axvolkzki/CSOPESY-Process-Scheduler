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

	std::shared_ptr<Process> createUniqueProcess(String name);
	std::shared_ptr<Process> findProcess(String name) const;

	std::shared_ptr<AScheduler> getScheduler();


private:
	GlobalScheduler();
	~GlobalScheduler() = default;
	GlobalScheduler(GlobalScheduler const&) {};
	GlobalScheduler& operator=(GlobalScheduler const&) {};
	static GlobalScheduler* sharedInstance;

	int pidCounter;
	std::shared_ptr<AScheduler> scheduler;

	String generateUniqueProcessName(int id);

	void initializeScheduler(const String& schedulerType);
};

