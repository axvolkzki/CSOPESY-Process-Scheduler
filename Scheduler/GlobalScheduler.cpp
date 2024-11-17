#include "GlobalScheduler.h"


// Define the static instance pointer
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

//void GlobalScheduler::tick() const
//{
//	this->scheduler->execute();
//}

std::shared_ptr<Process> GlobalScheduler::createUniqueProcess(String name, int totalLines)
{
	this->pidCounter = ConsoleManager::getInstance()->getProcessTableSize();
	this->pidCounter++;

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
	

	return newProcess;
}

//std::shared_ptr<Process> GlobalScheduler::findProcess(String name) const
//{
//	return this->scheduler->findProcess(name);
//}

String GlobalScheduler::generateUniqueProcessName(int id)
{
	std::stringstream ss;
	ss << "P" << id;
	return ss.str();
}

GlobalScheduler::GlobalScheduler() {
	pidCounter = 0;
	//scheduler = std::make_shared<AScheduler>();
}
