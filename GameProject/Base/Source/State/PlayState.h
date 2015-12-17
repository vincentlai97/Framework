#pragma once

#include "State.h"

class PlayState : public State
{
public:
	PlayState();
	~PlayState();

	virtual void Init();

	virtual void ChangeState(State *state);
	virtual void PushState(State *state);
	virtual void PopState();
};

