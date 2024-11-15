#include "MainConsole.h"



MainConsole::MainConsole() : AConsole("MainConsole")
{
}

void MainConsole::onEnabled()
{
	this->ASCIITextHeader();
}

void MainConsole::display()
{
}

void MainConsole::process()
{
	String commandMain;
	bool isValidCommand = false;
	this->isInitialized = false;

	while (isRunning) {
		std::cout << "Enter a command: ";
		std::getline(std::cin, commandMain);

		// Check if it is a valid initialize command
		if (this->isInitialized == false && this->isInitialCommand(commandMain)) {

			if (commandMain == "initialize") {
				this->isInitialized = true;
				std::cout << "Initialization successful." << std::endl;

				std::cout << std::endl;
				continue;	// Skip the rest of the loop
			}
			else if (commandMain == "exit") {
				this->isRunning = false;
				std::cout << "Exiting the program..." << std::endl;
			}
		}

		isValidCommand = this->validateCommand(commandMain);
		// Check if the program is initialized before proceeding
		if (this->isInitialized && isValidCommand) {
			

			if (isValidCommand) {
				if (commandMain == "clear") {
					system("cls");
					this->onEnabled();
					continue;	// Skip the rest of the loop
				}
				else if (commandMain == "exit") {
					this->isRunning = false;
					std::cout << "Exiting the program..." << std::endl;
				}
				else {
					this->commandRecognized(commandMain);
				}
			}
		}
		else {
			std::cerr << "Error: Application is not initialized. Please initialize the application first.\n" << std::endl;
		}
	}

	// Exit the program
	if (!this->isRunning) {
		ConsoleManager::getInstance()->exitApplication();
	}
}

void MainConsole::ASCIITextHeader() const
{
	std::cout << "  ____    ____      ___     ____    _______    ____    __   __		\n";
	std::cout << " / ___|  / ___|    / _ \\   |  _ \\   |  ___|   / ___|   \\ \\ / /	\n";
	std::cout << "| |      \\___ \\   | | | |  | |_) |  |  __|    \\___ \\    \\ V /	\n";
	std::cout << "| |___    ___) |  | |_| |  |  __/   | |___     ___) |    | |			\n";
	std::cout << " \\____|  |____/    \\___/   |_|      |_____|   |____/     |_|		\n";
	std::cout << "______________________________________________________________\n";
	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 10);
	std::cout << "Welcome to CSOPESY Emulator!\n";
	std::cout << "\n";
	displayDevelopers();
	std::cout << "______________________________________________________________\n";
	SetConsoleTextAttribute(console_color, 14);
	std::cout << "Type 'exit' to quit, 'clear' to clear the screen\n";
	SetConsoleTextAttribute(console_color, 15);
}

void MainConsole::displayDevelopers() const
{
	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 15);

	std::cout << "Developers: \n";
	std::cout << "1. Abenoja, Amelia Joyce L. \n";
	std::cout << "2. Cuales, Bianca Mari A. \n";
	std::cout << "\n";
	std::cout << "Last Updated: 15-11-2024\n";
}

bool MainConsole::isInitialCommand(String command) const
{
	bool isValid = false;

	String commandList[] = { "initialize", "exit" };

	String inputCommand = command.substr(0, command.find(" "));
	std::transform(inputCommand.begin(), inputCommand.end(), inputCommand.begin(), ::tolower);

	for (String cmd : commandList) {
		if (inputCommand == cmd) {
			isValid = true;
			break;
		}
	}

	return isValid;
}

bool MainConsole::validateCommand(String command) const
{
	bool isValid = false;

	String commandList[] = { "initialize", "exit", "clear",
							"scheduler-test", "scheduler-stop", "report-util",
							"screen" };

	String inputCommand = command.substr(0, command.find(" "));
	std::transform(inputCommand.begin(), inputCommand.end(), inputCommand.begin(), ::tolower);

	for (String cmd : commandList) {
		if (inputCommand == cmd) {
			isValid = true;
			break;
		}
	}

	return isValid;
}

void MainConsole::commandRecognized(String command) const
{
	std::cout << command << " command recognized. Doing something...\n" << std::endl;
}
