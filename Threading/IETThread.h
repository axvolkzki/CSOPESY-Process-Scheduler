#pragma once
#include <iostream>
#include <thread>
#include <chrono>

class IETThread
{
public:
	IETThread() = default;
	~IETThread() = default;

	void start();				// call to schedule execution
	static void sleep(int ms);

protected:
	virtual void run() = 0;		// customized thread inherits IETThread
};

