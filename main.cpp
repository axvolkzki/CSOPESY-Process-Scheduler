#include "Config/GlobalConfig.h"
#include "Console/ConsoleManager.h"

#include <Windows.h>

// Function Prototype
void SetConsoleWindow(int width, int height);


int main()
{
	GlobalConfig::initialize();
	GlobalConfig::getInstance()->loadConfigFile();

	ConsoleManager::initialize();

	bool running = true;
	while (running) {
		ConsoleManager::getInstance()->process();
		ConsoleManager::getInstance()->drawConsole();

		running = ConsoleManager::getInstance()->isRunning();
	}

	ConsoleManager::destroy();

	return 0;
}

/**
* Set the size of the console window.
 * @param width The width of the console window.
 * @param height The height of the console window.
 */
void SetConsoleWindow(int width, int height)
{
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const COORD newSize = { static_cast<short>(width), static_cast<short>(height) };
	SetConsoleScreenBufferSize(hConsole, newSize);

	const SMALL_RECT rect = { 0, 0, newSize.X - 1, newSize.Y - 1 };
	SetConsoleWindowInfo(hConsole, TRUE, &rect);
}