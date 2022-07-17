#include <iostream>
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
	

	float vertices[] = {
		// positions          // normals          // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,    0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
		0.5f, 0.5f, -0.5f,    0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,   0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
		0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f,    0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,    -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,   -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,    -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,     1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
		0.5f, 0.5f, 0.5f,     1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,    0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		0.5f, -0.5f, 0.5f,    0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,   0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		0.5f, 0.5f, -0.5f,    0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
		0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f
	};

	float texCoords[] = {
		0.0f, 0.0f, // lower-left corner
		1.0f, 0.0f, // lower-right corner
		0.5f, 1.0f // top-center corner
	};

	unsigned int indices[] = {
		0, 1, 2, 
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		0, 4, 5,
		0, 5, 1,

		3, 2, 6,
		3, 6, 7,

		3, 0, 4,
		3, 4, 7,

		2, 1, 5,
		2, 5, 6
	};

	//auto VAO = VertexArray();
	auto lightVAO = VertexArray();

	auto EBO = IndexBuffer(indices, sizeof(indices)/sizeof(float));
	EBO.Bind();

	auto VBO = VertexBuffer(vertices, sizeof(vertices));

	/*auto layout = VertexBufferLayout();
	layout.Push<float>(3);
	layout.Push<float>(2);*/

	auto layoutLight = VertexBufferLayout();
	layoutLight.Push<float>(3);
	layoutLight.Push<float>(3);
	layoutLight.Push<float>(2);

	//VAO.AddBuffer(VBO, layout);
	lightVAO.AddBuffer(VBO, layoutLight);

	Shader baseShader("../OpenProject/Resources/Shaders/Vertex.shader", "../OpenProject/Resources/Shaders/Fragment.shader");
	baseShader.Bind();

	baseShader.SetUniform3f("material.ambient", 0.3f, 0.1f, 0.8f);
	baseShader.SetUniform3f("material.diffuse", 0.3f, 0.1f, 0.8f);
	baseShader.SetUniform3f("material.specular", 0.3f, 0.1f, 0.8f);
	baseShader.SetUniform1f("material.shininess", 32.0f);

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(1.0f), glm::vec3(0.0, 0.0, 1.0));

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat3 normals = glm::mat3(1.0f);
	normals = glm::transpose(glm::inverse(model));

	glEnable(GL_DEPTH_TEST);

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
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

	glm::vec3 viewPos = glm::vec3(1.0f);
	glm::vec3 lightPos(0.8f, 1.4f, 2.0f);
	Shader lightShader("../OpenProject/Resources/Shaders/Vertex.shader", "../OpenProject/Resources/Shaders/LightingFragment.shader");
	
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	lightShader.Bind();
	lightShader.SetUniform4fv("model", glm::value_ptr(model));


	while (!glfwWindowShouldClose(window))
	{
		//std::cout << glfwGetTime() << std::endl;
		mainHandler.ProcessInput(window, glfwGetTime());

		lightVAO.Bind();

		model = glm::mat4(1.0f);
		glm::mat4 lightT = glm::mat4(1.0f);
		lightT = glm::rotate(lightT, glm::radians(0.002f), glm::vec3(0.0f, 1.0f, 0.0f));
		lightPos = glm::vec3(lightT * glm::vec4(lightPos, 1.0f));
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

		lightShader.Bind();
		lightShader.SetUniform4fv("model", glm::value_ptr(model));
		lightShader.SetUniform3f("lightColor", lightColor.x, lightColor.y, lightColor.z);
		lightShader.SetUniform4fv("view", glm::value_ptr(mainCamera.generateViewMatrix()));
		lightShader.SetUniform4fv("projection", glm::value_ptr(mainCamera.generateProjectionMatrix(800.0f / 600.0f, 0.1f, 100.0f)));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		normals = glm::transpose(glm::inverse(model));
		viewPos = mainCamera.GetPosition();

		baseShader.Bind();
		baseShader.SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);
		baseShader.SetUniform3f("viewPos", viewPos.x, viewPos.y, viewPos.z);
		baseShader.SetUniform4fv("model", glm::value_ptr(model));
		baseShader.SetUniform3fv("normals", glm::value_ptr(normals));
		baseShader.SetUniform4fv("view", glm::value_ptr(mainCamera.generateViewMatrix()));
		baseShader.SetUniform4fv("projection", glm::value_ptr(mainCamera.generateProjectionMatrix(800.0f / 600.0f, 0.1f, 100.0f)));
		baseShader.SetUniform3f("light.ambient", ambientColor.x, ambientColor.y, ambientColor.z);
		baseShader.SetUniform3f("light.diffuse", diffuseColor.x, diffuseColor.y, diffuseColor.z);
		baseShader.SetUniform3f("light.specular", lightColor.x, lightColor.y, lightColor.z);
		
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();

		//glClearColor(redValue, greenValue, 0.3f, 1.0f);
		glClearColor(0.05f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	glfwTerminate();
	return 0;
}