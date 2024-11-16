#pragma once
#include "IKeyboardEvent.h"

#include <iostream>


class KeyboardEventHandler : public IKeyboardEvent
{
public:
	void onKeyDown(char key) override;

	void onKeyUp(char key) override;
};

