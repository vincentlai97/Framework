#include "MyModel.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

//TEMP
#include "Projectile\Projectile.h"
#include "Projectile\Projectile-OBB.hpp"

MyModel::MyModel() : Model_3D()
{
	for (auto iter : all_weapon_commands)
		weapon_commands[iter] = false;
}

MyModel::~MyModel()
{
}

static Mesh *mesh;
static Object *object;
static SceneNode *node;

Projectile projectile;

void MyModel::Init()
{
	camera.Init(Vector3(0, 0, 5), Vector3(), Vector3(0, 1, 0));

	node = new SceneNode();
	mesh = MeshBuilder::GenerateOBJ("suzanne", "OBJ//suzanne.obj");
	mesh->textureID[0] = LoadTGA("Image//suzanne.tga");
	node->SetMesh(mesh);
	node->SetOBB(OrientedBoundingBox(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), -1.25, 1.25, -.9, .8, -0.9, 0.9));
	m_worldNode->AddChild("suzanne", node);
	m_spatialPartition->AddSceneNode(node);

	node = new SceneNode(*node);
	node->SetTransform(glm::mat4(1));
	node->Translate(glm::vec3(2.5, 1, -1));
	node->Rotate(30, glm::vec3(0, 1, 0));
	node->Rotate(-90, glm::vec3(0, 0, 1));
	node->SetOBB(OrientedBoundingBox(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), -1.25, 1.25, -.9, .8, -0.9, 0.9));
	m_worldNode->AddChild("suzanne2", node);
	m_spatialPartition->AddSceneNode(node);

	projectile.m_position = glm::vec3(0, 0, 0);
}

void MyModel::Update(double dt)
{
	Model_3D::Update(dt);

	SceneNode *suzanne = dynamic_cast<SceneNode*>(m_worldNode->GetChildNode("suzanne"));
	SceneNode *suzanne2 = dynamic_cast<SceneNode*>(m_worldNode->GetChildNode("suzanne2"));
	if (!suzanne->GetTransformedOBB(m_worldNode).CheckCollision(suzanne2->GetTransformedOBB(m_worldNode)))
		suzanne2->Rotate(dt * 10, glm::vec3(0, 0, 1));
	m_spatialPartition->Update(suzanne2);

	if (weapon_commands.at(WEAPON_COMMANDS::SHOOT))
	{
		projectile.m_position = glm::vec3(camera.position.x, camera.position.y, camera.position.z);
		projectile.m_direction = glm::vec3((camera.target - camera.position).x, (camera.target - camera.position).y, (camera.target - camera.position).z);
		projectile.m_speed = 50;
		projectile.m_lifespan = 500;
		m_projectileManager.AddProjectile(projectile);
	}

	m_projectileManager.Update(dt);
	for (auto &iter : m_projectileManager.GetProjectiles())
	{
		if (ProjectiletoOBB(iter).CheckCollision(suzanne2->GetTransformedOBB(m_worldNode)) && iter.m_lifespan < 1000)
		{
			projectile = Projectile(iter);
			projectile.m_lifespan = 5000;
			m_projectileManager.AddProjectile(projectile);
		}
	}
}