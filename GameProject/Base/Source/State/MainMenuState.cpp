#include "MainMenuState.h"

#include "PlayState.h"

#include "../MainMenuModel.h"
#include "../View.h"
#include "../MenuController.h"

MainMenuState::MainMenuState()
{
	model = new MainMenuModel();
	view = new View(model);
	controller = new MenuController(model, view);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::Init()
{
	model->Init();
	view->Init();
}

void MainMenuState::ChangeState(State *state)
{
}

void MainMenuState::PushState(State *state)
{
	if (dynamic_cast<PlayState*>(state))
	{
		state->view->setWindow(this->view->getWindow());
		state->Init();
	}
}

void MainMenuState::PopState()
{
}
