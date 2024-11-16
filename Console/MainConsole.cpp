#include "MainConsole.h"
#include "../Layout/DummyProcessLayout.h"



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
	isRunning = true;

	while (isRunning) {
		std::cout << "Enter a command: ";
		std::getline(std::cin, commandMain);

		// Check if it is a valid initialize command
		if (!this->isInitialized && this->isInitialCommand(commandMain) && this->isRunning) {

			if (commandMain == "initialize") {
				this->isInitialized = true;
				std::cout << "Initialization successful." << std::endl;

				std::cout << std::endl;
				continue;	// Skip the rest of the loop
			}
			else if (commandMain == "exit") {
				std::cout << "Exiting the program..." << std::endl;
				isRunning = false;
				ConsoleManager::getInstance()->exitApplication();
			}
		}

		
		isValidCommand = this->validateCommand(commandMain);
		// Check if the program is initialized before proceeding
		if (this->isInitialized && isValidCommand) {
			

			if (isValidCommand) {
				if (commandMain == "initialize") {
					std::cout << "The program is already initialized!" << std::endl;
				}
				else if (commandMain == "clear") {
					system("cls");
					this->onEnabled();
					continue;	// Skip the rest of the loop
				}
				else if (commandMain == "exit") {
					this->isRunning = false;
					std::cout << "Exiting the program..." << std::endl;
					ConsoleManager::getInstance()->exitApplication();
					isRunning = false;
				}
				else if (commandMain.substr(0, 6) == "screen") {
					if (this->validateScreenCommand(commandMain)) {
						
						if (commandMain.substr(0, 9) == "screen -s") {
							isRunning = false;
							this->executeScreenSwitchCommand(commandMain);
						}
						else if (commandMain.substr(0, 9) == "screen -r") {
							isRunning = false;
							this->executeScreenRedrawCommand(commandMain);
						}
						else if (commandMain.substr(0, 9) == "screen -l") {
							//this->executeScreenListCommand();
						}
					}
					else {
						std::cerr << "Error: Invalid screen command.\n";
					}
				}
				else if (commandMain == "dummy-layout") {
					this->executeDummyLayoutCommand();
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
							"screen",
							"dummy-layout" };

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

bool MainConsole::validateScreenCommand(String command) const
{
	bool isValid = false;

	String subString = command.substr(0, 9);

	if (subString == "screen -s" && command.length() > 9) {
		isValid = true;
	}
	else if (subString == "screen -r" && command.length() > 9) {
		isValid = true;
	}
	else if (subString == "screen -l" && command.length() == 9) {
		isValid = true;
	}

	if (subString == "screen -s" && command.length() == 9) {
		std::cerr << "Error: No screen name provided.\n";
	}
	else if (subString == "screen -r" && command.length() == 9) {
		std::cerr << "Error: No screen name provided.\n";
	}

	return isValid;
}

void MainConsole::executeScreenSwitchCommand(String command) const
{
	String screenName = command.substr(10, command.length());

	std::shared_ptr<Process> newProcess = this->createProcess(screenName);
	std::shared_ptr<BaseScreen> newScreen = std::make_shared<BaseScreen>(newProcess, screenName);

	ConsoleManager::getInstance()->registerScreen(newScreen);
	ConsoleManager::getInstance()->switchToScreen(screenName);
	ConsoleManager::getInstance()->process();
	ConsoleManager::getInstance()->drawConsole();
}

void MainConsole::executeScreenRedrawCommand(String command) const
{
	String screenName = command.substr(10, command.length());

	// get the process first
	std::shared_ptr<Process> currentProcess = ConsoleManager::getInstance()->getProcess(screenName);
	std::shared_ptr<BaseScreen> currentScreen = std::make_shared<BaseScreen>(currentProcess, screenName);
	ConsoleManager::getInstance()->registerScreen(currentScreen);
	ConsoleManager::getInstance()->switchToScreen(screenName);
	ConsoleManager::getInstance()->process();
	ConsoleManager::getInstance()->drawConsole();
}

void MainConsole::executeDummyLayoutCommand() const
{
	DummyProcessLayout dummyLayout;

	dummyLayout.displayCurrentDateTimes();
	dummyLayout.displayGPUSummaries();
	
	// Create a dummy process list for displayProcessList()
	std::vector<GPUProcess> processes = {
		{0, "N/A", "N/A", 1368, "C+G", "C:\\Windows\\System32\\dwm.exe", "N/A"},
		{0, "N/A", "N/A", 2116, "C+G", "...wekyb3d8bbwe\\XboxGameBarWidgets.exe", "N/A"},
		{0, "N/A", "N/A", 4224, "C+G", "...on\\123.0.2420.65\\msedgewebview2.exe", "N/A"},
		{0, "N/A", "N/A", 5684, "C+G", "C:\\Windows\\explorer.exe", "N/A"},
		{0, "N/A", "N/A", 6676, "C+G", "...nt.CBS_cw5n1h2txyewy\\SearchHost.exe", "N/A"},
		{0, "N/A", "N/A", 6700, "C+G", "...2txyewy\\StartMenuExperienceHost.exe", "N/A"}
	};

	// Call displayProcessList() with the dummy data
	dummyLayout.displayProcessList(processes);

	std::cout << std::endl;
}

std::shared_ptr<Process> MainConsole::createProcess(String processName) const
{
	// Create a process
	std::shared_ptr<Process> process = std::make_shared<Process>(processName, 100);

	// Add the process in the list
	ConsoleManager::getInstance()->addProcess(process);

	return process;
	
}
