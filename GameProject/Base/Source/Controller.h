#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model.h"
#include "View.h"

#include <windows.h>

class Controller 
{
public:
	Controller(Model* model, View* view) : model(model), view(view) {}

	virtual void Init();
	virtual void RunLoop();
	virtual void Update(double dt);

protected:
	Model* model;
	View* view;

	double m_dElapsedTime; // delta time

	bool IsKeyPressed(int key) { return glfwGetKey(view->getWindow(), key) == GLFW_PRESS; }

};

#endif