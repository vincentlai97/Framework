#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "State.h"

#include <stack>

class StateManager
{
public:
	~StateManager() { if (instance != nullptr) delete instance; instance = nullptr; }

	static StateManager* GetInstance();
	static State* GetCurrentState();

	static void ChangeState(State *state);
	static void PushState(State *state);
	static void PopState();

private:
	static StateManager *instance;
	static std::stack<State*> m_statesStack;

	StateManager() {}

};

#endif