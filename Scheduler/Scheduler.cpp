#include "Scheduler.h"
#include <mutex>



Scheduler* Scheduler::sharedInstance = nullptr;

Scheduler* Scheduler::getInstance()
{
	return sharedInstance;
}

void Scheduler::initialize()
{
	sharedInstance = new Scheduler();
}

void Scheduler::destroy()
{
	delete sharedInstance;
}

void Scheduler::stopScheduler()
{
	this->isRunning = false;
	if (schedulerThread.joinable()) {
		schedulerThread.join();
	}
}

void Scheduler::startSchedulerThread(String scheduler, int delay, int quantum)
{
	if (this->isRunning == false) {
		this->isRunning = true;

		if (scheduler == "fcfs") {
			schedulerThread = std::thread(&Scheduler::runFCFSScheduler, this, delay);
			schedulerThread.detach();
			
		}
		else if (scheduler == "rr") {
			schedulerThread = std::thread(&Scheduler::runRoundRobinScheduler, this, delay, quantum);
			schedulerThread.detach();
		}
	}
}

std::shared_ptr<Process> Scheduler::createUniqueProcess()
{
	int totalLines = GlobalConfig::getInstance()->getRandomInstructionCount();
	int pidCounter = ConsoleManager::getInstance()->getProcessTableSize();
	pidCounter += 1;

	String name = this->generateUniqueProcessName(pidCounter);

	std::shared_ptr<Process> existingProcess = this->findProcess(name);

	if (existingProcess != nullptr) {
		return existingProcess;
	}
	else {
		std::shared_ptr<Process> newProcess = std::make_shared<Process>(pidCounter, name);
		newProcess->generateRandomProcess(totalLines);

		this->addProcessToReadyQueue(newProcess);

		return newProcess;
	}
}

std::shared_ptr<Process> Scheduler::findProcess(String name) const
{
	return ConsoleManager::getInstance()->findProcess(name);

}

void Scheduler::displaySchedulerStatus()
{
	int availableCPUCount = 0;

	for (int i = 0; i < this->cpuCoreList.size(); i++) {
		if (this->cpuCoreList[i]->isAvailable()) {
			availableCPUCount += 1;
		}
	}

	float cpuUtil = (this->numCPU - availableCPUCount) / this->numCPU * 100;

	std::cout << "CPU Utilization: " << cpuUtil << "%" << std::endl;
	std::cout << "Cores used: " << this->numCPU - availableCPUCount << std::endl;
	std::cout << "Cores available: " << availableCPUCount << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < 38; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;

	std::cout << "Running processes:" << std::endl;
	for (int i = 0; i < this->cpuCoreList.size(); i++) {
		std::shared_ptr<CPUCore> cpuCore = this->cpuCoreList[i];
		if (!cpuCore->isAvailable()) {
			String processName = cpuCore->getProcessName();
			int commandCounter = cpuCore->getCommandCounter();
			int linesOfCode = cpuCore->getLinesOfCode();
			int cpuCoreID = cpuCore->getCPUCoreID();

			auto arrivalTime = cpuCore->getArrivalTime();

			// format the arrival time : (mm/dd/yyyy, hh:mm:ss AM/PM)
			char buffer[64];
			std::strftime(buffer, sizeof(buffer), "%m/%d/%Y, %I:%M:%S %p", &arrivalTime);



			std::cout << processName << "\t" << "(" << buffer << ")" << "\t" << "Core: " << cpuCoreID << "\t" << commandCounter << " / " << linesOfCode << std::endl;
		}
		/*else {
			std::cout << "Core " << cpuCore->getCPUCoreID() << ": " << "Idle" << std::endl;
		}*/
	}

	std::cout << std::endl;
	for (int i = 0; i < 38; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;

	std::cout << "Finished processes:" << std::endl;

	for (int i = 0; i < this->processList.size(); i++) {
		std::shared_ptr<Process> process = this->processList[i];
		if (process->getState() == Process::ProcessState::FINISHED) {
			
			String processName = process->getName();
			int commandCounter = process->getCommandCounter();
			int linesOfCode = process->getLinesOfCode();
			int cpuCoreID = process->getCPUCoreID();

			auto arrivalTime = process->getArrivalTime();

			// format the arrival time : (mm/dd/yyyy, hh:mm:ss AM/PM)
			char buffer[64];
			std::strftime(buffer, sizeof(buffer), "%m/%d/%Y, %I:%M:%S %p", &arrivalTime);

			std::cout << processName << "\t" << "(" << buffer << ")" << "\t" << "FINISHED" << "\t" << commandCounter << " / " << linesOfCode << std::endl;
		}
	}
}

String Scheduler::generateUniqueProcessName(int id)
{
	std::stringstream ss;
	ss << "Process_" << id;
	return ss.str();
}

void Scheduler::addProcessToReadyQueue(std::shared_ptr<Process> process)
{
	//std::lock_guard<std::mutex> lock(this->schedulerMutex);
	this->readyQueue.push(process);
	this->processList.push_back(process);

	// debugger:
	//std::cout << "Process " << process->getName() << " added to ready queue" << std::endl;
}

void Scheduler::runFCFSScheduler(int delay)
{
	while (this->isRunning) {
		//std::lock_guard<std::mutex> lock(schedulerMutex);

		for (int i = 0; i < this->cpuCoreList.size(); i++) {
			std::shared_ptr<CPUCore> cpuCore = this->cpuCoreList[i];

			if (cpuCore->isAvailable()) {
				if (!this->readyQueue.empty()) {
					std::shared_ptr<Process> process = this->readyQueue.front();
					this->readyQueue.pop();

					cpuCore->assignProcess(process);

					/*while (!process->isFinished()) {
						process->executeCurrentCommand();
						process->moveToNextLine();

						Sleep(delay);
					}*/
				}
			}



			/*if (this->readyQueue.size() > 0) {
				std::shared_ptr<Process> process = this->readyQueue.front();
				this->readyQueue.pop();

				int cpuCoreID = process->getCPUCoreID();
				this->cpuCoreList[cpuCoreID]->assignProcess(process);

				ConsoleManager::getInstance()->addProcess(process);
				ConsoleManager::getInstance()->switchConsole(SCHEDULING_CONSOLE_NAME);

				while (!process->isFinished()) {
					process->executeCurrentCommand();
					process->moveToNextLine();

					ConsoleManager::getInstance()->drawConsole();
					Sleep(delay);
				}

				this->cpuCoreList[cpuCoreID]->removeProcess();
			}*/
		}
	}
}

void Scheduler::runRoundRobinScheduler(int delay, int quantum)
{
	int cpuCycleCounter = 0;

	while (this->isRunning) {
		for (int i = 0; i < this->cpuCoreList.size(); i++) {
			std::shared_ptr<CPUCore> cpuCore = this->cpuCoreList[i];

			if (cpuCore->isAvailable()) {
				if (!this->readyQueue.empty()) {
					// Get the next process from the ready queue
					std::shared_ptr<Process> process = this->readyQueue.front();
					this->readyQueue.pop();

					// Assign process to CPU core
					cpuCore->assignProcess(process);

					// Run the process for one quantum
					int elapsedTime = 0;

					// Execute commands for the process until quantum is finished or process is done
					while (elapsedTime < quantum && !process->isFinished()) {

						//process->executeCurrentCommand();
						process->moveToNextLine();
						elapsedTime++;

						std::this_thread::sleep_for(std::chrono::milliseconds(delay));
					}

					// If the process is not finished, push it back to the ready queue
					if (!process->isFinished()) {
						this->readyQueue.push(process);
					}
					/*else {
						std::cout << "Process " << process->getName() << " finished.\n";
					}*/
					cpuCore->assignProcess(nullptr);  // Free the CPU core
				}
			}
		}

		// Sleep for the specified delay to simulate CPU cycles
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));

		cpuCycleCounter++;
	}
}

Scheduler::Scheduler()
{
	this->numCPU = GlobalConfig::getInstance()->getNumCPU();
	this->bacthProcessFrequency = GlobalConfig::getInstance()->getBatchProcessFreq();
	this->minInstructions = GlobalConfig::getInstance()->getMinIns();
	this->maxInstructions = GlobalConfig::getInstance()->getMaxIns();

	for (int i = 0; i < this->numCPU; i++) {
		std::shared_ptr<CPUCore> cpuCore = std::make_shared<CPUCore>();
		this->cpuCoreList.push_back(cpuCore);
	}

	String scheduler = GlobalConfig::getInstance()->getScheduler();
	this->startSchedulerThread(scheduler, this->bacthProcessFrequency, GlobalConfig::getInstance()->getQuantumCycles());
}