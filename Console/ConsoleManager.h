#pragma once
#include "../TypeDefRepo.h"
#include "../Console/AConsole.h"
#include "../Screen/BaseScreen.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "Windows.h"



const String MAIN_CONSOLE_NAME = "MAIN_CONSOLE";
const String MARQUEE_CONSOLE_NAME = "MARQUEE_CONSOLE";
const String SCHEDULING_CONSOLE_NAME = "SCHEDULING_CONSOLE";
const String MEMORY_CONSOLE_NAME = "MEMORY_CONSOLE";

class ConsoleManager
{
public:
	typedef std::unordered_map<String, std::shared_ptr<AConsole>> ConsoleTable;			// Collection of key value pairs

	static ConsoleManager* getInstance();
	static void initialize();
	static void destroy();

	void drawConsole() const;
	void process() const;
	void switchConsole(String consoleName);

	void registerScreen(std::shared_ptr<BaseScreen> screenRef);
	void switchToScreen(String screenName);
	void unregisteredScreen(String screenName);

	void returnToPreviousConsole();
	void exitApplication();
	bool isRunning() const;

	HANDLE getConsoleHandle() const;

	void setCursorPosition(int x, int y) const;

	// Add a process to the list
	void addProcess(std::shared_ptr<Process> processName);
	std::shared_ptr<Process> getProcess(String processName);

private:
	ConsoleManager();
	~ConsoleManager() = default;
	ConsoleManager(ConsoleManager const&) {};	// copy constructor is private
	ConsoleManager& operator=(ConsoleManager const&) {};	// assignment operator is private
	static ConsoleManager* sharedInstance;

	ConsoleTable consoleTable;
	std::shared_ptr<AConsole> currentConsole;
	std::shared_ptr<AConsole> previousConsole;
	
	HANDLE consoleHandle;
	bool running = true;

	std::vector<std::shared_ptr<Process>> processList;
};

