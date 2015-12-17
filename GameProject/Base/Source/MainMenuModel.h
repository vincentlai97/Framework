#pragma once

#include "MenuModel.h"

class MainMenuModel : public MenuModel
{
public:
	MainMenuModel();
	~MainMenuModel();

	virtual void Init();
	virtual void Update(double dt);
};

