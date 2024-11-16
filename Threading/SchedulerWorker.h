#pragma once
#include "IETThread.h"

class SchedulerWorker : public IETThread
{
public:
	ScchedulerWorker() = default;
	void update(bool isRunning);
	void run() override;

private:
	bool isRunning = true;
};

