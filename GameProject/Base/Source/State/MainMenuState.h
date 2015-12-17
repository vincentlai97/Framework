#pragma once

#include "State.h"

class MainMenuState : public State
{
public:
	MainMenuState();
	~MainMenuState();

	virtual void Init();

	virtual void ChangeState(State *state);
	virtual void PushState(State *state);
	virtual void PopState();
};

