#pragma once

#include "glm/glm.hpp"

class Camera
{
public:
	bool rollReversed = false;

	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3 look = glm::vec3(0.0f, 0.0f, -1.0f));

	void RotateByYaw(float angleDelta);
	void RotateByPitch(float angleDelta);
	void RotateByRoll(float angleDelta);

	virtual void MoveInForwardDirection(const float& time, const bool& forward, const bool& shifted);
	void MoveByDash(const float& time, const bool& rightward, const bool& shifted);
	void MoveVertically(const float& time, const bool& upward, const bool& shifted);

	glm::mat4 generateProjectionMatrix(float aspect, float near, float far);
	glm::mat4 generateViewMatrix();

	void ChangeZoom(float angleDelta);

	float GetFov() { return fov; }
private:
	glm::vec3 position;

	float yaw;
	float pitch;
	float roll;

	glm::vec3 CameraUpNormalized;
	//distinguish between look and move for case of moving only on plane(FPS like camera)
	glm::vec3 ForwardMoveNormalized;
	glm::vec3 LookNormalized;
	glm::vec3 RightNormalized;

	float fov = 45.0f;
	float speed = 5.0f;
	float shiftedFactor = 3.0f;
};
