#include "PlayState.h"

#include "../MyModel.h"
#include "../MyView.h"
#include "../Controller_3D.h"

PlayState::PlayState()
{
	model = new MyModel();
	view = new MyView(model);
	controller = new Controller_3D(model, view);
}

PlayState::~PlayState()
{
}

void PlayState::Init()
{
	model->Init();
	view->Init();
}

void PlayState::ChangeState(State *state)
{
}

void PlayState::PushState(State *state)
{
}

void PlayState::PopState()
{
}