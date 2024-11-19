#include "GlobalScheduler.h"
#include "FCFSScheduler.h"



GlobalScheduler* GlobalScheduler::sharedInstance = nullptr;
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

std::shared_ptr<Process> GlobalScheduler::createUniqueProcess(String name)
{
	int totalLines = GlobalConfig::getInstance()->getRandomInstructionCount();
	this->pidCounter = ConsoleManager::getInstance()->getProcessTableSize();
	this->pidCounter++;

	name = this->generateUniqueProcessName(this->pidCounter);

	/*std::shared_ptr<Process> existingProcess = this->findProcess(name);

	if (existingProcess != nullptr) {
		return existingProcess;
	}
	else {
		if (name == "") {
			name = this->generateUniqueProcessName(this->pidCounter);
		}
	}*/

	std::shared_ptr<Process> newProcess = std::make_shared<Process>(this->pidCounter, name);
	newProcess->generateRandomProcess(totalLines);

	// put new process to ready queue
	//this->scheduler->addProcess(newProcess);

	// add process to process table
	ConsoleManager::getInstance()->addProcess(newProcess);
	

	return newProcess;
}

std::shared_ptr<Process> GlobalScheduler::findProcess(String name) const
{
	return this->scheduler->findProcess(name);
}

std::shared_ptr<AScheduler> GlobalScheduler::getScheduler()
{
	return this->scheduler;
}

void GlobalScheduler::initializeScheduler(const String& schedulerType)
{
	if (schedulerType == "fcfs") {
		scheduler = std::make_shared<FCFSScheduler>(0, "Global_FCFS");
	}
}

String GlobalScheduler::generateUniqueProcessName(int id)
{
	std::stringstream ss;
	ss << "P" << id;
	return ss.str();
}

GlobalScheduler::GlobalScheduler() {
	this->pidCounter = 0;
	//this->scheduler = nullptr;	// Initialize the scheduler to null
	String schedulerType = GlobalConfig::getInstance()->getScheduler();
	this->initializeScheduler(schedulerType);
}
