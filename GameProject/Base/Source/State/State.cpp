#include "State.h"

State::State()
{
}

State::~State()
{
	if (model != nullptr) delete model;
	model = nullptr;
	if (view != nullptr) delete view;
	view = nullptr;
	if (controller != nullptr) delete controller;
	controller = nullptr;
}