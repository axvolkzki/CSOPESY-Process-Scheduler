#pragma once
#include <map>
#include <memory>


#include "../TypeDefRepo.h"
#include "../Process/Process.h"

class GlobalScheduler
{
public:
	typedef std::map<int, String> ProcessTable;

	static GlobalScheduler* getInstance();
	static void initialize();
	static void destroy();
	
	void tick() const;

	std::shared_ptr<Process> createUniqueProcess(String name);
	std::shared_ptr<Process> findProcess(String name) const;

private:
	GlobalScheduler();
	~GlobalScheduler() = default;
	GlobalScheduler(GlobalScheduler const&) {};
	GlobalScheduler& operator=(GlobalScheduler const&) {};
	static GlobalScheduler* sharedInstance;

	ProcessTable processTable;
	std::shared_ptr<AScheduler> scheduler;
};

