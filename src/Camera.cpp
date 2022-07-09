#include "Camera.h"
#include "glm/glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 look)
{	
	position = pos;
	ForwardMoveNormalized = glm::vec3(0.0f, 0.0f, 0.0f);
	LookNormalized = glm::normalize(look);
	RightNormalized = glm::normalize(glm::cross(look, glm::vec3(0.0f, 1.0f, 0.0f)));
	CameraUpNormalized = glm::cross(RightNormalized, look);
	pitch = 0.0f;
	yaw = -90.0f;
	roll = 0.0f;

	float clampedAngle = fmodf(pitch, 360.0f);
	rollReversed = (clampedAngle >= 90.0f && clampedAngle <= 270.0f) || (clampedAngle <= -90.0f && clampedAngle >= -270.0f) ? true : false;
}

void Camera::RotateByYaw(float angleDelta)
{
	yaw += angleDelta;
	LookNormalized.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	LookNormalized.y = sin(glm::radians(pitch));
	LookNormalized.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	LookNormalized = glm::normalize(LookNormalized);
	RightNormalized = glm::normalize(glm::cross(LookNormalized, glm::vec3(0.0f, 1.0f, 0.0f)));
	CameraUpNormalized = glm::cross(RightNormalized, LookNormalized);
}

void Camera::RotateByPitch(float angleDelta)
{
	pitch += angleDelta;
	float clampedAngle = fmodf(pitch, 360.0f);
	if (!rollReversed)
	{
		if ((clampedAngle >= 90.0f && clampedAngle <= 270.0f) || (clampedAngle <= -90.0f && clampedAngle >= -270.0f))
		{
			roll *= -1;
			rollReversed = !rollReversed;
		}
	}
	else
	{
		if (!(clampedAngle >= 90.0f && clampedAngle <= 270.0f) && !(clampedAngle <= -90.0f && clampedAngle >= -270.0f))
		{
			roll *= -1;
			rollReversed = !rollReversed;
		}
	}
	
	LookNormalized.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	LookNormalized.y = sin(glm::radians(pitch));
	LookNormalized.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	LookNormalized = glm::normalize(LookNormalized);
	RightNormalized = glm::normalize(glm::cross(LookNormalized, glm::vec3(0.0f, 1.0f, 0.0f)));
	CameraUpNormalized = glm::cross(RightNormalized, LookNormalized);
}

void Camera::RotateByRoll(float angleDelta)
{
	roll += 0.0f;
}


void Camera::MoveInForwardDirection(const float& time, const bool& forward, const bool& shifted)
{
	//FPS-like movement
	/*ForwardMoveNormalized.x = LookNormalized.x;
	ForwardMoveNormalized.z = LookNormalized.z;
	ForwardMoveNormalized = glm::normalize(ForwardMoveNormalized);*/
	ForwardMoveNormalized = LookNormalized;
	float shiftedTime = time;
	if (shifted)
	{
		shiftedTime *= shiftedFactor;
	}

	if (forward)
	{
		position += ForwardMoveNormalized * speed * shiftedTime;
	}
	else
	{
		position -= ForwardMoveNormalized * speed * shiftedTime;
	}
}

void Camera::MoveByDash(const float& time, const bool& rightward, const bool& shifted)
{
	float shiftedTime = time;
	if (shifted)
	{
		shiftedTime *= shiftedFactor;
	}

	if (rightward)
	{
		position += RightNormalized * speed * shiftedTime;
	}
	else
	{
		position -= RightNormalized * speed * shiftedTime;
	}
}

void Camera::MoveVertically(const float& time, const bool& upward, const bool& shifted)
{
	float shiftedTime = time;
	if (shifted)
	{
		shiftedTime *= shiftedFactor;
	}

	if (upward)
	{
		position += glm::vec3(0.0f, 1.0f, 0.0f) * speed * shiftedTime;
	}
	else
	{
		position -= glm::vec3(0.0f, 1.0f, 0.0f) * speed * shiftedTime;
	}
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
	view = glm::lookAt(position, position + LookNormalized, CameraUpNormalized);

	if (rollReversed)
	{

	}

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
