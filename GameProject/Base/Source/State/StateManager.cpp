#include "StateManager.h"

StateManager* StateManager::instance = nullptr;
std::stack<State*> StateManager::m_statesStack;

StateManager* StateManager::GetInstance()
{
	if (instance == nullptr) instance = new StateManager();

	return instance;
}

State* StateManager::GetCurrentState()
{
	if (m_statesStack.empty()) return nullptr;
	return m_statesStack.top();
}

void StateManager::ChangeState(State *state)
{
	if (!m_statesStack.empty())
	{
		m_statesStack.top()->ChangeState(state);
		m_statesStack.top()->~State();
		m_statesStack.top() = state;
	}
}

void StateManager::PushState(State *state)
{
	if (!m_statesStack.empty()) m_statesStack.top()->PushState(state);
	m_statesStack.push(state);
}

void StateManager::PopState()
{
	m_statesStack.pop();
}