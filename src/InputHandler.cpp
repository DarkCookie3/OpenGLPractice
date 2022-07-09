#include "InputHandler.h"
#include <iostream>

void InputHandler::ProcessInput(GLFWwindow* window, float currentTime)
{
	static float deltaTime = 0.0f;
	static float lastFrame = 0.0f;

	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;

	if(deltaTime >= 0.01f)
	std::cout << deltaTime << std::endl;

	bool shifted = false;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		shifted = true;
		
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.MoveInForwardDirection(deltaTime, true, shifted);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.MoveInForwardDirection(deltaTime, false, shifted);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.MoveByDash(deltaTime, false, shifted);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.MoveByDash(deltaTime, true, shifted);

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.MoveVertically(deltaTime, false, shifted);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.MoveVertically(deltaTime, true, shifted);
}

void InputHandler::mouse_callback(double xpos, double ypos)
{
	static float lastX = 0.0f;
	static float lastY = 0.0f;
	static bool firstMouse = true;
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	xoffset *= HorizontalSensetivity*float(camera.rollReversed);
	yoffset *= VerticalSensetivity;
	camera.RotateByYaw(xoffset);
	camera.RotateByPitch(yoffset);
}

void InputHandler::scroll_callback(double xoffset, double yoffset)
{
	camera.ChangeZoom(yoffset);
}