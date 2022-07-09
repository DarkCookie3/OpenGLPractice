#pragma once

#include "Camera.h"
#include <memory>
#include "GLFW/glfw3.h"

class InputHandler
{
public:
	InputHandler(Camera& cam) : camera(cam)
	{
	}

	InputHandler(Camera& cam, float VSens, float HSens) 
		: camera(cam), VerticalSensetivity(VSens), HorizontalSensetivity(HSens)
	{
	}

	void SetSensetivity(float VSens, float HSens)
	{
		VerticalSensetivity = VSens;
		HorizontalSensetivity = HSens;
	}

	void SetCurrentCamera(Camera& cam)
	{
		camera = cam;
	}

	void ProcessInput(GLFWwindow* window, float currentTime);

	void mouse_callback(double xpos, double ypos);
	void scroll_callback(double xoffset, double yoffset);

private:
	Camera& camera;
	float VerticalSensetivity = 0.05f;
	float HorizontalSensetivity = 0.05f;
};