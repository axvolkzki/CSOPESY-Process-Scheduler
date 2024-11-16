#include "GlobalScheduler.h"

GlobalScheduler* GlobalScheduler::getInstance()
{
	return sharedInstance;
}

void GlobalScheduler::initialize()
{
	sharedInstance = new GlobalScheduler();
}

void GlobalScheduler::destroy()
{
	delete sharedInstance;
}

void GlobalScheduler::tick() const
{
	this->scheduler->execute();
}
