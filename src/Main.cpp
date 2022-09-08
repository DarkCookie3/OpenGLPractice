#include <iostream>
#include <map>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"

#include "glm/glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "Camera.h"
#include "InputHandler.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Assimp/config.h"
#include "Model.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static Camera mainCamera = Camera();
static InputHandler mainHandler = InputHandler(mainCamera);

void mouseWrapper(GLFWwindow* window, double x, double y)
{
	mainHandler.mouse_callback(x, y);
}

void scrollWrapper(GLFWwindow* window, double x, double y)
{
	mainHandler.scroll_callback(x, y);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseWrapper);
	glfwSetScrollCallback(window, scrollWrapper);
	
	Model backpack("E:/OpenGLPractice/OpenProject/Resources/Models/Backpack/backpack.obj");
	
	float vertices[] = {
		// back face
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  0.0f, 0.0f, // bottom-left 
		0.5f, 0.5f, -0.5f,   0.0f, 0.0f, -1.0f,  1.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f, // bottom-right
		0.5f, 0.5f, -0.5f,   0.0f, 0.0f, -1.0f,  1.0f, 1.0f, // top-right
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  0.0f, 0.0f, // bottom-left
		-0.5f, 0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f, // top-left
		// front face
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom-left
		0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // bottom-right
		0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // top-right
		0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // top-right
		-0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // top-left
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom-left
		// left face
		-0.5f, 0.5f, 0.5f,   -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // top-right
		-0.5f, 0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top-left
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f, 0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // bottom-right
		-0.5f, 0.5f, 0.5f,   -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // top-right
		// right face
		0.5f, 0.5f, 0.5f,   1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // top-left
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // bottom-right
		0.5f, 0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // bottom-right
		0.5f, 0.5f, 0.5f,   1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // top-left
		0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // bottom-left
		// bottom face
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,  0.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f, // top-left 
		0.5f, -0.5f, 0.5f,   0.0f, -1.0f, 0.0f,  1.0f, 0.0f, // bottom-left
		0.5f, -0.5f, 0.5f,   0.0f, -1.0f, 0.0f,  1.0f, 0.0f, // bottom-left
		-0.5f, -0.5f, 0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f, // bottom-right
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,  0.0f, 1.0f, // top-right
		// top face
		-0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, // top-left
		0.5f, 0.5f, 0.5f,    0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom-right
		0.5f, 0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f, // top-right
		0.5f, 0.5f, 0.5f,    0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom-right
		-0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, // top-left
		-0.5f, 0.5f, 0.5f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f // bottom-left
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-2.3f, 1.0f, -3.5f)
	};

	float quad[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f
	};

	unsigned int quadIndices[] = {
		2, 1, 0,
		0, 3, 2
	};

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f, 0.2f, 2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-2.0f, 2.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, -3.0f)
	};

	std::vector<glm::vec3> vegetation;
	vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
	vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
	vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
	vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));

	auto cubeVAO = VertexArray();
	auto quadVAO = VertexArray();

	auto VBO = VertexBuffer(vertices, sizeof(vertices));
	auto quadVBO = VertexBuffer(quad, sizeof(quad));

	auto layout = VertexBufferLayout();
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);

	cubeVAO.AddBuffer(VBO, layout);
	quadVAO.AddBuffer(quadVBO, layout);

	quadVAO.Bind();
	auto quadEBO = IndexBuffer(&quadIndices[0], sizeof(quadIndices) / sizeof(quadIndices[0]));
	quadEBO.Bind();

	Shader baseShader("../OpenProject/Resources/Shaders/Vertex.shader", "../OpenProject/Resources/Shaders/Fragment.shader");
	Shader solidColorShader("../OpenProject/Resources/Shaders/Vertex.shader", "../OpenProject/Resources/Shaders/SolidColorFragment.shader");
	Shader screenShader("../OpenProject/Resources/Shaders/VertexFrame.shader", "../OpenProject/Resources/Shaders/FragmentFrame.shader");
	Shader mirrorShader("../OpenProject/Resources/Shaders/Vertex.shader", "../OpenProject/Resources/Shaders/FragmentFrame.shader");

	baseShader.Bind();
	baseShader.SetUniform1f("material.shininess", 32.0f);
	baseShader.SetUniform3f("dirLights[0].direction", -0.2f, -1.0f, -0.3f);
	baseShader.SetUniform3f("dirLights[0].ambient", 0.05f, 0.05f, 0.05f);
	baseShader.SetUniform3f("dirLights[0].diffuse", 0.4f, 0.4f, 0.4f);
	baseShader.SetUniform3f("dirLights[0].specular", 0.5f, 0.5f, 0.5f);
	
	baseShader.SetUniform3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	baseShader.SetUniform3f("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	baseShader.SetUniform3f("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	baseShader.SetUniform1f("pointLights[0].constant", 1.0f);
	baseShader.SetUniform1f("pointLights[0].linear", 0.09f);
	baseShader.SetUniform1f("pointLights[0].quadratic", 0.032f);
	
	baseShader.SetUniform3f("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	baseShader.SetUniform3f("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	baseShader.SetUniform3f("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	baseShader.SetUniform1f("pointLights[1].constant", 1.0f);
	baseShader.SetUniform1f("pointLights[1].linear", 0.09f);
	baseShader.SetUniform1f("pointLights[1].quadratic", 0.032f);
	
	baseShader.SetUniform3f("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	baseShader.SetUniform3f("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
	baseShader.SetUniform3f("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	baseShader.SetUniform1f("pointLights[2].constant", 1.0f);
	baseShader.SetUniform1f("pointLights[2].linear", 0.09f);
	baseShader.SetUniform1f("pointLights[2].quadratic", 0.032f);
	
	baseShader.SetUniform3f("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	baseShader.SetUniform3f("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
	baseShader.SetUniform3f("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	baseShader.SetUniform1f("pointLights[3].constant", 1.0f);
	baseShader.SetUniform1f("pointLights[3].linear", 0.09f);
	baseShader.SetUniform1f("pointLights[3].quadratic", 0.032f);
	
	baseShader.SetUniform3f("spotLights[0].ambient", 0.0f, 0.0f, 0.0f);
	baseShader.SetUniform3f("spotLights[0].diffuse", 1.0f, 1.0f, 1.0f);
	baseShader.SetUniform3f("spotLights[0].specular", 1.0f, 1.0f, 1.0f);
	baseShader.SetUniform1f("spotLights[0].constant", 1.0f);
	baseShader.SetUniform1f("spotLights[0].linear", 0.09f);
	baseShader.SetUniform1f("spotLights[0].quadratic", 0.032f);
	baseShader.SetUniform1f("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
	baseShader.SetUniform1f("spotLights[0].cutOffOuter", glm::cos(glm::radians(15.0f)));

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat3 normals = glm::mat3(1.0f);

	glm::vec3 viewPos = glm::vec3(1.0f);
	glm::vec3 lookDir = glm::vec3(1.0f);

	Shader lightShader("../OpenProject/Resources/Shaders/Vertex.shader", "../OpenProject/Resources/Shaders/LightingFragment.shader");
	
	Texture crate("../OpenProject/Resources/Textures/Crate.jpg", TextureType::diffuse);
	Texture crateSpec("../OpenProject/Resources/Textures/CrateSpecular.jpg", TextureType::specular);

	Texture vegetationTexture("../OpenProject/Resources/Textures/VegetationBlue.png", TextureType::diffuse);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_STENCIL_TEST);
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	unsigned int texColorBuffer;
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	while (!glfwWindowShouldClose(window))
	{
		mainHandler.ProcessInput(window, glfwGetTime());

		cubeVAO.Bind();

		model = glm::mat4(1.0f);

		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f)/2.0f + 1.0f;
		lightColor.y = sin(glfwGetTime() * 0.7f)/2.0f + 1.0f;
		lightColor.z = sin(glfwGetTime() * 1.3f)/2.0f + 1.0f;
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.8f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
	
		glm::vec3 camPos = mainCamera.GetPosition();
		glm::vec3 camLook = mainCamera.GetLookDirection();
		mainCamera.SetPosition(glm::vec3(camPos.x, camPos.y, camPos.z));
		mainCamera.SetLookDirection(glm::vec3(camLook.x, camLook.y, camLook.z));

		lightShader.Bind();
		lightShader.SetUniform4fv("model", glm::value_ptr(model));
		lightShader.SetUniform3f("lightColor", lightColor.x, lightColor.y, lightColor.z);
		lightShader.SetUniform4fv("view", glm::value_ptr(mainCamera.generateViewMatrix()));
		lightShader.SetUniform4fv("projection", glm::value_ptr(mainCamera.generateProjectionMatrix(800.0f / 600.0f, 0.1f, 100.0f)));
		
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);

		for (unsigned int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++)
		{
			glm::mat4 lightT = glm::mat4(1.0f);
			lightT = glm::rotate(lightT, glm::radians(0.002f), glm::vec3(0.0f, 1.0f, 0.0f));
			pointLightPositions[i] = glm::vec3(lightT * glm::vec4(pointLightPositions[i], 1.0f));

			glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::translate(trans, pointLightPositions[i]);
			trans = glm::scale(trans, glm::vec3(0.2f));

			normals = glm::transpose(glm::inverse(trans));

			lightShader.SetUniform4fv("model", glm::value_ptr(trans));
			lightShader.SetUniform3fv("normals", glm::value_ptr(normals));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		viewPos = mainCamera.GetPosition();	
		lookDir = mainCamera.GetLookDirection();

		solidColorShader.Bind();
		solidColorShader.SetUniform4fv("view", glm::value_ptr(mainCamera.generateViewMatrix()));
		solidColorShader.SetUniform4fv("projection", glm::value_ptr(mainCamera.generateProjectionMatrix(800.0f / 600.0f, 0.1f, 100.0f)));

		baseShader.Bind();
		baseShader.SetUniform3f("viewPos", viewPos.x, viewPos.y, viewPos.z);
		baseShader.SetUniform4fv("view", glm::value_ptr(mainCamera.generateViewMatrix()));
		baseShader.SetUniform4fv("projection", glm::value_ptr(mainCamera.generateProjectionMatrix(800.0f / 600.0f, 0.1f, 100.0f)));

		// point light 1
		baseShader.SetUniform3f("pointLights[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		// point light 2
		baseShader.SetUniform3f("pointLights[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		// point light 3
		baseShader.SetUniform3f("pointLights[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		// point light 4
		baseShader.SetUniform3f("pointLights[3].position", pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		// spotLight
		baseShader.SetUniform3f("spotLights[0].position", viewPos.x, viewPos.y, viewPos.z);
		baseShader.SetUniform3f("spotLights[0].direction", lookDir.x, lookDir.y, lookDir.z);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.0f, 2.0f, -12.0f));
		normals = glm::transpose(glm::inverse(model));
		baseShader.SetUniform4fv("model", glm::value_ptr(model));
		baseShader.SetUniform3fv("normals", glm::value_ptr(normals));
		backpack.Draw(baseShader);

		cubeVAO.Bind();
		crate.Bind(0);
		crateSpec.Bind(1);
		for (unsigned int i = 0; i < sizeof(cubePositions)/sizeof(cubePositions[0]); i++)
		{
			glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::translate(trans, cubePositions[i]);
			float angle = 20.0f * i;
			trans = glm::rotate(trans, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			normals = glm::transpose(glm::inverse(trans));
			baseShader.SetUniform4fv("model", glm::value_ptr(trans));
			baseShader.SetUniform3fv("normals", glm::value_ptr(normals));
			glm::vec4 test = glm::vec4(vegetation[3], 1.0) * model;
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);

		cubeVAO.Bind();
		solidColorShader.Bind();
		for (unsigned int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++)
		{
			glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::translate(trans, cubePositions[i]);
			float angle = 20.0f * i;
			trans = glm::rotate(trans, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			trans = glm::scale(trans, glm::vec3(1.1f, 1.1f, 1.1f));
			solidColorShader.SetUniform4fv("model", glm::value_ptr(trans));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glEnable(GL_DEPTH_TEST);

		std::map<float, glm::vec3> sorted;
		for (unsigned int i = 0; i < vegetation.size(); i++)
		{
			float distance = glm::length(viewPos - vegetation[i]);
			sorted[distance] = vegetation[i];
		}

		quadVAO.Bind();
		baseShader.Bind();
		vegetationTexture.Bind(0);
		baseShader.SetUniform1i("material.texture_specular1", 0);
		for (std::map<float, glm::vec3>::reverse_iterator i = sorted.rbegin(); i != sorted.rend(); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, i->second);
			normals = glm::transpose(glm::inverse(model));
			baseShader.SetUniform4fv("model", glm::value_ptr(model));
			baseShader.SetUniform3fv("normals", glm::value_ptr(normals));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0); 
		glClearColor(0.6f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		mainCamera.SetPosition(camPos);
		mainCamera.SetLookDirection(glm::vec3(camLook));






		glDisable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL_TEST);
		mirrorShader.Bind();
		model = glm::mat4(1.0f);
		normals = model;
		mirrorShader.SetUniform4fv("model", glm::value_ptr(model));
		mirrorShader.SetUniform3fv("normals", glm::value_ptr(normals));
		mirrorShader.SetUniform4fv("view", glm::value_ptr(mainCamera.generateViewMatrix()));
		mirrorShader.SetUniform4fv("projection", glm::value_ptr(mainCamera.generateProjectionMatrix(800.0f / 600.0f, 0.1f, 100.0f)));
		quadVAO.Bind();
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();	
	}
	glDeleteFramebuffers(1, &framebuffer);
	glfwTerminate();
	return 0;
}