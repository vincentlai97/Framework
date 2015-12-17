#include "MainMenuModel.h"

#include "State\StateManager.h"
#include "State\PlayState.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

MainMenuModel::MainMenuModel() : MenuModel()
{
}

MainMenuModel::~MainMenuModel()
{
}

Mesh *mesh;
Object *object;
Object *_arrow;

void MainMenuModel::Init()
{
	mesh = MeshBuilder::GenerateQuad("background", Color(1, 0, 1), 1);
	mesh->textureID[0] = LoadTGA("Image//MainMenu.tga");
	object = new Object(mesh);
	object->scale = glm::scale<float>(102.4, 80, 1);
	object->translation = glm::translate(0, 0, 0);
	m_objectList.push_back(object);

	mesh = MeshBuilder::GenerateQuad("arrow", Color(1, 0, 1), 1);
	mesh->textureID[0] = LoadTGA("Image//arrow.tga");
	object = new Object(mesh);
	object->scale = glm::scale(7, 7, 1);
	object->translation = glm::translate(-18, 5, 1);
	m_objectList.push_back(object);
	_arrow = object;
}

const std::array<float, 3> arrowPos = {
	5, 
	-2, 
	-9
};
static int _arrowPos = 0;

const float c_buttonBuffer = 0.5f;

void MainMenuModel::Update(double dt)
{
	static float buttonBuffer = 0.f;
	if (key_commands.at(KEY_COMMANDS::UP) && buttonBuffer > c_buttonBuffer)
	{
		--_arrowPos;
		if (_arrowPos < 0) _arrowPos += 3;
		_arrow->translation = glm::translate<float>(-18, arrowPos[_arrowPos], 1);
		buttonBuffer = 0;
	}
	if (key_commands.at(KEY_COMMANDS::DOWN) && buttonBuffer > c_buttonBuffer)
	{
		++_arrowPos;
		if (_arrowPos > 3) _arrowPos -= 3;
		_arrow->translation = glm::translate<float>(-18, arrowPos[_arrowPos], 1);
		buttonBuffer = 0;
	}
	buttonBuffer += dt;

	if (key_commands.at(KEY_COMMANDS::ENTER))
	{
		if (_arrowPos == 0)
		{
			StateManager::PushState(new PlayState());
		}
		else if (_arrowPos == 2)
		{
			StateManager::PopState();
		}
	}

	ResetCommands();
}