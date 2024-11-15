#include "BaseScreen.h"

BaseScreen::BaseScreen(std::shared_ptr<Process> process, String processName) : AConsole(processName)
{
	this->attachedProcess = process;
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

	std::cout << "root:\\>";

	// Read user input
	String command;
	std::getline(std::cin, command);

	if (command == "clear" || command == "cls") {
		system("cls");
	}
	else if (command == "process-smi") {
		this->printProcessInfo();
	}
	else if (command == "exit") {
		ConsoleManager::getInstance()->returnToPreviousConsole();
		ConsoleManager::getInstance()->unregisteredScreen(this->name);
	}
}

void BaseScreen::display()
{
}

void BaseScreen::printProcessInfo()
{
	/*std::cout << "Process Name: " << this->attachedProcess->getName() << std::endl;
	std::cout << "Current line of instruction / Total lines of instruction: " << this->attachedProcess->getCurrentLine() << " / " << this->attachedProcess->getTotalLines() << std::endl;
	std::cout << "Timestamp: " << this->attachedProcess->getTimestamp() << std::endl;*/
}
