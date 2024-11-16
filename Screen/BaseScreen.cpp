#include "BaseScreen.h"

#include "../Console/ConsoleManager.h"

BaseScreen::BaseScreen(std::shared_ptr<Process> process, String processName) : AConsole(processName), attachedProcess(process)
{
}

void BaseScreen::onEnabled()
{
}

void BaseScreen::process()
{
	if (this->refreshed == false) {
		this->refreshed = true;
		this->printProcessInfo();
	}

	std::cout << "\nroot:\\>";

	// Read user input
	String command;
	std::getline(std::cin, command);

	if (command == "clear" || command == "cls") {
		system("cls");
	}
	else if (command == "process-smi") {
		this->printProcessInfo();
		std::cout << std::endl;
	}
	else if (command == "exit") {
		system("cls");
		ConsoleManager::getInstance()->returnToPreviousConsole();
		ConsoleManager::getInstance()->unregisteredScreen(this->name);
	}
	else {
		std::cout << "Unrecognized command: " << command << std::endl;
	}
}

void BaseScreen::display()
{
	this->printProcessInfo();
}

void BaseScreen::printProcessInfo()
{
	std::cout << "This is a base screen. A method for information display." << std::endl;
	std::cout << "Process Name: " << this->attachedProcess->getName() << std::endl;
	std::cout << "Current line of instruction / Total lines of instruction: "
		<< this->attachedProcess->getCommandCounter() << " / "
		<< this->attachedProcess->getLinesOfCode() << std::endl;

	std::tm arrivalTime = this->attachedProcess->getArrivalTime(); // Store the r-value in a local variable
	std::cout << "Timestamp: " << std::put_time(&arrivalTime, "%Y-%m-%d %H:%M:%S") << std::endl;
}

