#include "MyModel.h"

#include "MeshBuilder.h"
#include "LoadTGA.h"

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
	camera.Init(Vector3(0, 5, 5), Vector3(), Vector3(0, 1, 0));

	//Floor
	node = new SceneNode();
	mesh = MeshBuilder::GenerateQuad("floor", Color(0, 0, -0.3f), 200.f);
	mesh->textureID[0] = LoadTGA("Image//floor.tga");
	node->SetMesh(mesh);
	node->Rotate(-90, glm::vec3(1, 0, 0));
	m_worldNode->AddChild("floor", node);

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

	m_TPC.m_camera = &(this->camera);
	m_TPC.m_object = dynamic_cast<SceneNode*>(m_worldNode->GetChildNode("suzanne"));
	m_TPC.m_cameraOffset = glm::vec3(-1, 1, -2);
	m_TPC.m_direction = glm::vec3(0, 0, 1);
	m_TPC.m_up = glm::vec3(0, 1, 0);

	projectile.m_position = glm::vec3(0, 0, 0);
}

#define CAMERA_SPEED 50.f

std::map<Model_3D::CAMERA_MOVEMENT, void (ThirdPersonCamera::*)(float)> func_third_person_camera_movement = {
	{ Model_3D::CAMERA_MOVEMENT::MOVE_FORWARD, &ThirdPersonCamera::MoveForward },
	{ Model_3D::CAMERA_MOVEMENT::MOVE_BACKWARD, &ThirdPersonCamera::MoveBackward },
	{ Model_3D::CAMERA_MOVEMENT::MOVE_LEFT, &ThirdPersonCamera::MoveLeft },
	{ Model_3D::CAMERA_MOVEMENT::MOVE_RIGHT, &ThirdPersonCamera::MoveRight }
};
std::map<Model_3D::CAMERA_ROTATION, void (ThirdPersonCamera::*)(float)> func_third_person_camera_rotation = {
	{ Model_3D::CAMERA_ROTATION::ROTATE_UP, &ThirdPersonCamera::LookUp },
	{ Model_3D::CAMERA_ROTATION::ROTATE_LEFT, &ThirdPersonCamera::LookLeft }
};

void MyModel::Update(double dt)
{
	for (auto iter : all_camera_movement)
	if (camera_movement.at(iter))
		(m_TPC.*(func_third_person_camera_movement.at(iter)))(dt * CAMERA_SPEED);

	for (auto iter : all_camera_rotation)
		(m_TPC.*(func_third_person_camera_rotation.at(iter)))(camera_rotation.at(iter) * 0.1f);

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

	ResetCameraMovement();
	ResetCameraRotation();
}