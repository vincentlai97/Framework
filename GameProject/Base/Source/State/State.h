#ifndef STATE_H
#define STATE_H

#include "../Model.h"
#include "../View.h"
#include "../Controller.h"

class State
{
public:
	State();
	~State();

	virtual void Init() = 0;

	virtual void ChangeState(State *state) = 0;
	virtual void PushState(State *state) = 0;
	virtual void PopState() = 0;

//private:
	Model *model;
	View *view;
	Controller *controller;

};

#endif