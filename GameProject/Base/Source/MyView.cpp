#include "MyView.h"

#include "MyModel.h"

#ifdef RENDEROBB
#include "OrientedBoundingBox.h"
#include "MeshBuilder.h"
#include "Projectile\Projectile-OBB.hpp"
#endif

MyView::MyView(Model *model) : View_3D(model)
{
}

MyView::~MyView()
{
}

#define camera m_model->getCamera()

void MyView::Render()
{
#if VIEW_DIMENSIONS == 2
	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	projectionStack.push(glm::ortho(-(float)windowWidth / 20, (float)windowWidth / 20, -(float)windowHeight / 20, (float)windowHeight / 20, -1000.f, 1000.f));
	viewStack.push(glm::mat4(1.f));
#else if VIEW_DIMENSIONS == 3
	projectionStack.push(glm::perspective(45.f, 4.f / 3.f, .1f, 10000.f));
	viewStack.push(glm::lookAt(
		glm::vec3(camera.position.x, camera.position.y, camera.position.z),
		glm::vec3(camera.target.x, camera.target.y, camera.target.z),
		glm::vec3(camera.up.x, camera.up.y, camera.up.z)
		));
#endif
	modelStack.push(glm::mat4(1.f));

	GeometryPass();

	RenderObjectList(m_model->getObjectList());
	RenderWorldSceneNode(m_model->getWorldNode());

	MyModel *model = dynamic_cast<MyModel*>(m_model);
	Mesh *projectile = MeshBuilder::GenerateSphere("bullet", Color(1, 0, 0), 8, 8, 0.1f);
#ifdef RENDEROBB
	Mesh *OBBFrame = MeshBuilder::GenerateCube("obbframe", Color(1, 0, 0), 1.f);
#endif
	for (auto iter : model->GetProjectileManager().GetProjectiles())
	{
		modelStack.push(modelStack.top()); {
			modelStack.top() *= glm::translate(iter.m_position);

			RenderMesh(projectile, false);

		} modelStack.pop();
#ifdef RENDEROBB
			OrientedBoundingBox OBB = ProjectiletoOBB(iter);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_CULL_FACE);
			glLineWidth(5.f);
			modelStack.push(modelStack.top()); {
				modelStack.top() *= glm::translate(OBB.GetCentre());
				modelStack.top() *= glm::rotate(-90 + glm::degrees(glm::atan(OBB.GetFrontAxis().x, OBB.GetFrontAxis().z)), glm::vec3(0, 1, 0));
				modelStack.top() *= glm::rotate(glm::degrees(glm::asin(OBB.GetFrontAxis().y)), glm::vec3(0, 0, 1));
				modelStack.top() *= glm::translate<float>(OBB.GetLengths()[FRONT_AXIS][MIN_LENGTH], OBB.GetLengths()[UP_AXIS][MIN_LENGTH], OBB.GetLengths()[RIGHT_AXIS][MIN_LENGTH]);
				modelStack.top() *= glm::scale<float>(OBB.GetSize());
				modelStack.top() *= glm::translate<float>(0.5, 0.5, 0.5);
				RenderMesh(OBBFrame, false);
			} modelStack.pop();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_CULL_FACE);
			glLineWidth(1.f);
#endif
	}

	LightPass();

	projectionStack.pop();
	viewStack.pop();
	modelStack.pop();
}

#undef camera