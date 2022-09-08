#pragma once

#include "glm/glm.hpp"

class Camera
{
public:
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3 look = glm::vec3(0.0f, 0.0f, -1.0f));

	void RotateByYaw(const float& angleDelta);
	void RotateByPitch(const float& angleDelta);
	void RotateByRoll(const float& time);

	void MoveInForwardDirection(const float& time, const bool& shifted);
	void MoveByDash(const float& time, const bool& shifted);
	void MoveVertically(const float& time);

	glm::mat4 generateProjectionMatrix(float aspect, float near, float far);
	glm::mat4 generateViewMatrix();

	void ChangeZoom(float angleDelta);
	void SetPosition(glm::vec3 arg);
	void SetLookDirection(glm::vec3 arg);

	float GetFov() const { return fov; }
	glm::vec3 GetPosition() const { return position; }
	glm::vec3 GetLookDirection() const { return LookNormalized; }
private:
	glm::vec3 position;

	float yaw;
	float pitch;
	float roll;

	glm::vec3 CameraUpNormalized;
	glm::vec3 ForwardMoveNormalized;
	glm::vec3 YawRotationUp;
	glm::vec3 LookNormalized;
	glm::vec3 RightNormalized;

	float fov = 45.0f;
	float speed = 5.0f;
	float rollSpeed = 80.0f;
	float shiftedFactor = 3.0f;
};
