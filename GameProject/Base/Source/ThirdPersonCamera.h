#ifndef THIRD_PERSON_CAMERA_H
#define THIRD_PERSON_CAMERA_H

#include "Camera3.h"
#include "Scene Graph\SceneNode.h"

#include "glm.hpp"

class ThirdPersonCamera
{
public:
	ThirdPersonCamera();
	~ThirdPersonCamera();

	virtual void MoveForward(const float dist);
	virtual void MoveBackward(const float dist);
	virtual void MoveLeft(const float dist);
	virtual void MoveRight(const float dist);

	virtual void LookUp(const float angle);
	virtual void LookDown(const float angle);
	virtual void LookLeft(const float angle);
	virtual void LookRight(const float angle);

//private:
	Camera3 *m_camera;
	SceneNode *m_object;

	glm::vec3 m_cameraOffset;
	glm::vec3 m_direction;
	glm::vec3 m_up;

	virtual void UpdateCamera();
};

#endif