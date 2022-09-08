#include "Camera.h"
#include "glm/glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "iostream"

Camera::Camera(glm::vec3 pos, glm::vec3 look)
{	
	//stub constructor, fix it
	position = pos;
	ForwardMoveNormalized = glm::vec3(0.0f, 0.0f, 0.0f);
	LookNormalized = glm::normalize(look);
	RightNormalized = glm::normalize(glm::cross(look, glm::vec3(0.0f, 1.0f, 0.0f)));
	CameraUpNormalized = glm::cross(RightNormalized, look);
	YawRotationUp = CameraUpNormalized;
	pitch = 0.0f;
	yaw = -90.0f;
	roll = 0.0f;
}

void Camera::RotateByYaw(const float& angleDelta)
{
	yaw += angleDelta;
	
	glm::mat4 yawT(1.0f);	

	yawT = glm::rotate(yawT, glm::radians(-angleDelta), YawRotationUp);

	LookNormalized = glm::vec3(yawT * glm::vec4(LookNormalized, 1.0));
	RightNormalized = glm::vec3(yawT * glm::vec4(RightNormalized, 1.0));
	CameraUpNormalized = glm::vec3(yawT * glm::vec4(CameraUpNormalized, 1.0));
}

void Camera::RotateByPitch(const float& angleDelta)
{
	pitch += angleDelta;
	glm::mat4 pitchT(1.0f);

	pitchT = glm::rotate(pitchT, glm::radians(angleDelta), RightNormalized);

	LookNormalized = glm::vec3(pitchT * glm::vec4(LookNormalized, 1.0));
	CameraUpNormalized = glm::vec3(pitchT * glm::vec4(CameraUpNormalized, 1.0));
}

void Camera::RotateByRoll(const float& time)
{	
	float angleDelta = time * rollSpeed;

	roll += angleDelta;

	glm::mat4 rollT(1.0f);

	rollT = glm::rotate(rollT, glm::radians(angleDelta), LookNormalized);

	RightNormalized = glm::vec3(rollT * glm::vec4(RightNormalized, 1.0));
	CameraUpNormalized = glm::vec3(rollT * glm::vec4(CameraUpNormalized, 1.0));
	YawRotationUp = glm::vec3(rollT * glm::vec4(YawRotationUp, 1.0));
}


void Camera::MoveInForwardDirection(const float& time, const bool& shifted)
{
	ForwardMoveNormalized = LookNormalized;
	float shiftedTime = time;
	if (shifted)
	{
		shiftedTime *= shiftedFactor;
	}
	position += ForwardMoveNormalized * speed * shiftedTime;
}

void Camera::MoveByDash(const float& time, const bool& shifted)
{
	float shiftedTime = time;
	if (shifted)
	{
		shiftedTime *= shiftedFactor;
	}
	position += RightNormalized * speed * shiftedTime;
}

void Camera::MoveVertically(const float& time)
{
	float shiftedTime = time;
	position += CameraUpNormalized * speed * shiftedTime;
}

glm::mat4 Camera::generateProjectionMatrix(float aspect, float near, float far)
{
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(fov), aspect, near, far);
	return projection;
}

glm::mat4 Camera::generateViewMatrix()
{
	glm::mat4 view;
	//up vector is already calculated, because CameraUpNormalized is it; Change lookAt to manual matrix filling
	view = glm::lookAt(position, position + LookNormalized, CameraUpNormalized);
	return view;
}

void Camera::ChangeZoom(float angleDelta)
{
	fov -= angleDelta;
	if (fov >= 135.0f)
	{
		fov = 135.0f;
	}
	else if (fov <= 0.5f)
	{
		fov = 0.5f;
	}
}
