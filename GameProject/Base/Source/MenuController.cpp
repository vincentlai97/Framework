#include "MenuController.h"

#include "MenuModel.h"

MenuController::MenuController(Model *model, View *view) : Controller(model, view)
{
}

MenuController::~MenuController()
{
}

void MenuController::Update(double dt)
{
	MenuModel *model = dynamic_cast<MenuModel*>(this->model);
	if (glfwGetKey(view->getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
		model->SetCommands(MenuModel::KEY_COMMANDS::UP);
	if (glfwGetKey(view->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) model->SetCommands(MenuModel::KEY_COMMANDS::DOWN);
	if (glfwGetKey(view->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) model->SetCommands(MenuModel::KEY_COMMANDS::LEFT);
	if (glfwGetKey(view->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) model->SetCommands(MenuModel::KEY_COMMANDS::RIGHT);
	if (glfwGetKey(view->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS) model->SetCommands(MenuModel::KEY_COMMANDS::ENTER);

	Controller::Update(dt);
}