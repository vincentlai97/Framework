#pragma once

#include "Model.h"

class MenuModel :
	public Model
{
public:
	enum class KEY_COMMANDS {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		ENTER
	};

	enum class MOUSE_CLICK {
		BUTTON_1
	};

	MenuModel();
	~MenuModel();

	virtual void SetCommands(KEY_COMMANDS command) { key_commands.at(command) = true; }
	virtual void SetCommands(MOUSE_CLICK command) { mouse_click.at(command) = true; }

protected:
	std::map<KEY_COMMANDS, bool> key_commands;
	std::map<MOUSE_CLICK, bool> mouse_click;

	virtual void ResetCommands();
};

#define NUM_KEY_COMMANDS 5U
const std::array<MenuModel::KEY_COMMANDS, NUM_KEY_COMMANDS> all_key_commands = {
	MenuModel::KEY_COMMANDS::UP,
	MenuModel::KEY_COMMANDS::DOWN,
	MenuModel::KEY_COMMANDS::LEFT,
	MenuModel::KEY_COMMANDS::RIGHT,
	MenuModel::KEY_COMMANDS::ENTER
};

#define NUM_MOUSE_CLICK 1U
const std::array<MenuModel::MOUSE_CLICK, NUM_MOUSE_CLICK> all_mouse_click = {
	MenuModel::MOUSE_CLICK::BUTTON_1
};