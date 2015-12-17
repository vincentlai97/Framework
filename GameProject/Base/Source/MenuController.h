#pragma once

#include "Controller.h"

class MenuController : public Controller
{
public:
	MenuController(Model *model, View *view);
	~MenuController();

	virtual void Update(double dt);
};

