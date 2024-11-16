#pragma once
#include <iostream>
#include <Windows.h>
#include <algorithm>



#include "AConsole.h"
#include "../TypeDefRepo.h"
#include "ConsoleManager.h"
#include "../Process/Process.h"

class MainConsole : public AConsole
{
public:
	MainConsole();
	void onEnabled() override;
	void display() override;
	void process() override;

private:
	bool isInitialized = false;
	bool isRunning = true;

	void ASCIITextHeader() const;
	void displayDevelopers() const;

	bool isInitialCommand(String command) const;		// Check if it is initialize command or exit command
	bool validateCommand(String command) const;			// Check if the command is valid
	void commandRecognized(String command) const;		// Display message that the command is recognized
	bool validateScreenCommand(String command) const;	// Check if the command is a screen command

	void executeScreenSwitchCommand(String command) const;
	void executeScreenRedrawCommand(String command) const;
	void executeScreenListCommand() const;
	void executeSchedulerTestCommand() const;
	void executeSchedulerStopCommand() const;
	void executeReportUtilizationCommand() const;

	void executeDummyLayoutCommand() const;

	std::shared_ptr<Process> createProcess(String processName) const;

};

	