#include <stdio.h> //Include the standard C++ headers
#include <stdlib.h>

#include <GL/glew.h> //Include GLEW
#include <GLFW/glfw3.h> //Include GLFW
#include <glm.hpp>

#include "State\StateManager.h"
#include "State\State.h"
#include "State\MainMenuState.h"

#include "Model.h"
#include "Model_3D.h"
#include "MyModel.h"
#include "View.h"
#include "View_3D.h"
#include "MyView.h"
#include "Controller.h"
#include "Controller_3D.h"

#include "timer.h"

static int window_width = 1024, window_height = 800;
static char window_title[] = { "2SPOOPY4U" };

const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
static double m_dElapsedTime = 0.0;
static double m_dAccumulatedTime_ThreadOne = 0.0;
static double m_dAccumulatedTime_ThreadTwo = 0.0;
static StopWatch m_timer;

void main( void )
{
	StateManager::GetInstance();

	Model* model = new Model();
	View* view = new View(model);
	Controller* controller = new Controller(model, view);

	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
	GLFWwindow *window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);

	//If the window couldn't be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(window);

	glewExperimental = true; // Needed for core profile
	// Initialize GLEW
	if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);

	State *state = new MainMenuState();
	state->view->setWindow(window);
	state->Init();
	StateManager::GetInstance()->PushState(state);

	glfwSetInputMode(StateManager::GetCurrentState()->view->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	m_timer.startTimer();
	m_dElapsedTime = m_timer.getElapsedTime();
	while (!glfwWindowShouldClose(StateManager::GetCurrentState()->view->getWindow()) && !(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS))
	{
		// Get the elapsed time
		m_dElapsedTime = m_timer.getElapsedTime();
		m_dAccumulatedTime_ThreadOne += m_dElapsedTime;
		m_dAccumulatedTime_ThreadTwo += m_dElapsedTime;
		StateManager::GetCurrentState()->controller->Update(m_dElapsedTime);
		if (StateManager::GetCurrentState() == nullptr) break;
		std::cout << m_dElapsedTime << std::endl;
		StateManager::GetCurrentState()->view->Render();
		//Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
		m_timer.waitUntil(frameTime); // Frame rate limiter. Limits each frame to a specified time in ms.   
	}

	if (model != NULL) delete model;
	if (view != NULL) delete view;
	if (controller != NULL) delete controller;
}