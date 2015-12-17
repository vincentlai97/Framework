#include "ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera()
{
}

ThirdPersonCamera::~ThirdPersonCamera()
{
}

void ThirdPersonCamera::MoveForward(const float dist)
{
	m_object->PostTranslate(glm::normalize(glm::vec3(m_direction.x, 0, m_direction.z)) * dist);
	UpdateCamera();
}

void ThirdPersonCamera::MoveBackward(const float dist)
{
	m_object->PostTranslate(glm::normalize(-glm::vec3(m_direction.x, 0, m_direction.z)) * dist);
	UpdateCamera();
}

void ThirdPersonCamera::MoveLeft(const float dist)
{
	m_object->PostTranslate(glm::normalize(-glm::cross(m_direction, glm::vec3(0, 1, 0))) * dist);
	UpdateCamera();
}

void ThirdPersonCamera::MoveRight(const float dist)
{
	m_object->PostTranslate(glm::normalize(glm::cross(m_direction, glm::vec3(0, 1, 0))) * dist);
	UpdateCamera();
}

void ThirdPersonCamera::LookUp(const float angle)
{
	glm::vec3 right = glm::cross(m_direction, m_up);
	right.y = 0;
	right = glm::normalize(right);
	m_direction = glm::normalize(glm::vec3(glm::rotate(-angle, right) * glm::vec4(m_direction, 0)));
	m_up = glm::normalize(glm::vec3(glm::rotate(-angle, right) * glm::vec4(m_up, 0)));
	UpdateCamera();
}

void ThirdPersonCamera::LookDown(const float angle)
{
	glm::vec3 right = glm::cross(m_direction, m_up);
	right.y = 0;
	right = glm::normalize(right);
	m_direction = glm::normalize(glm::vec3(glm::rotate(-angle, right) * glm::vec4(m_direction, 0)));
	m_up = glm::normalize(glm::vec3(glm::rotate(-angle, right) * glm::vec4(m_up, 0)));
	UpdateCamera();
}

void ThirdPersonCamera::LookLeft(const float angle)
{
	m_object->Rotate(-angle, glm::vec3(0, 1, 0));
	m_direction = glm::normalize(glm::vec3(glm::rotate(-angle, glm::vec3(0, 1, 0)) * glm::vec4(m_direction, 0)));
	m_up = glm::normalize(glm::vec3(glm::rotate(-angle, glm::vec3(0, 1, 0)) * glm::vec4(m_up, 0)));
	UpdateCamera();
}

void ThirdPersonCamera::LookRight(const float angle)
{
	m_direction = glm::normalize(glm::vec3(glm::rotate(angle, glm::vec3(0, 1, 0)) * glm::vec4(m_direction, 0)));
	m_up = glm::normalize(glm::vec3(glm::rotate(angle, glm::vec3(0, 1, 0)) * glm::vec4(m_up, 0)));
	m_object->Rotate(angle, glm::vec3(0, 1, 0));
	UpdateCamera();
}


void ThirdPersonCamera::UpdateCamera()
{
	m_camera->position.Set(m_object->GetTransform()[3][0], m_object->GetTransform()[3][1], m_object->GetTransform()[3][2]);
	glm::vec3 offset = glm::vec3(glm::rotate(glm::degrees(glm::atan(m_direction.x, m_direction.z)), glm::vec3(0, 1, 0)) * glm::vec4(m_cameraOffset, 0));
	m_camera->position += Vector3(offset.x, offset.y, offset.z);
	m_camera->target = m_camera->position + Vector3(m_direction.x, m_direction.y, m_direction.z).Normalized();
	m_camera->up = Vector3(m_up.x, m_up.y, m_up.z);
	//printf("%f, %f, %f\n", offset.x, offset.y, offset.z);
}