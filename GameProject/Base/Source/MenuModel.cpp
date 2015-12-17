#include "MenuModel.h"

MenuModel::MenuModel()
{
	for (auto iter : all_key_commands)
		key_commands[iter] = false;

	for (auto iter : all_mouse_click)
		mouse_click[iter] = false;
}

MenuModel::~MenuModel()
{
}

void MenuModel::ResetCommands()
{
	for (auto iter : all_key_commands)
		key_commands[iter] = false;

	for (auto iter : all_mouse_click)
		mouse_click[iter] = false;
}