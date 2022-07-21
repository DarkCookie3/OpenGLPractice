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

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f, 0.2f, 2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-2.0f, 2.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, -3.0f)
	};

	//auto VAO = VertexArray();
	auto lightVAO = VertexArray();

	auto VBO = VertexBuffer(vertices, sizeof(vertices));

	auto layoutLight = VertexBufferLayout();
	layoutLight.Push<float>(3);
	layoutLight.Push<float>(3);
	layoutLight.Push<float>(2);

	//VAO.AddBuffer(VBO, layout);
	lightVAO.AddBuffer(VBO, layoutLight);

	Shader baseShader("../OpenProject/Resources/Shaders/Vertex.shader", "../OpenProject/Resources/Shaders/Fragment.shader");
	baseShader.Bind();

	Texture Edward = Texture("../OpenProject/Resources/Textures/Edward.jpg");
	Edward.Bind(0);
	
	Texture EdwardSpecular = Texture("../OpenProject/Resources/Textures/EdwardSpecular.jpg");
	EdwardSpecular.Bind(1);

	baseShader.SetUniform1i("material.diffuse", 0);
	baseShader.SetUniform1i("material.specular", 1);
	baseShader.SetUniform1f("material.shininess", 32.0f);

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat3 normals = glm::mat3(1.0f);

	glEnable(GL_DEPTH_TEST);

	glm::vec3 viewPos = glm::vec3(1.0f);
	glm::vec3 lookDir = glm::vec3(1.0f);

	Shader lightShader("../OpenProject/Resources/Shaders/Vertex.shader", "../OpenProject/Resources/Shaders/LightingFragment.shader");

	while (!glfwWindowShouldClose(window))
	{
		mainHandler.ProcessInput(window, glfwGetTime());

		lightVAO.Bind();

		model = glm::mat4(1.0f);

		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f)/2.0f + 1.0f;
		lightColor.y = sin(glfwGetTime() * 0.7f)/2.0f + 1.0f;
		lightColor.z = sin(glfwGetTime() * 1.3f)/2.0f + 1.0f;
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.85f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.3f);

		lightShader.Bind();
		lightShader.SetUniform4fv("model", glm::value_ptr(model));
		lightShader.SetUniform3f("lightColor", lightColor.x, lightColor.y, lightColor.z);
		lightShader.SetUniform4fv("view", glm::value_ptr(mainCamera.generateViewMatrix()));
		lightShader.SetUniform4fv("projection", glm::value_ptr(mainCamera.generateProjectionMatrix(800.0f / 600.0f, 0.1f, 100.0f)));
		
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

		Edward.Bind(0);
		EdwardSpecular.Bind(1);

		baseShader.Bind();
		baseShader.SetUniform3f("viewPos", viewPos.x, viewPos.y, viewPos.z);
		baseShader.SetUniform4fv("view", glm::value_ptr(mainCamera.generateViewMatrix()));
		baseShader.SetUniform4fv("projection", glm::value_ptr(mainCamera.generateProjectionMatrix(800.0f / 600.0f, 0.1f, 100.0f)));

		
		// directional light
		baseShader.SetUniform3f("dirLights[0].direction", -0.2f, -1.0f, -0.3f);
		baseShader.SetUniform3f("dirLights[0].ambient", 0.05f, 0.05f, 0.05f);
		baseShader.SetUniform3f("dirLights[0].diffuse", 0.4f, 0.4f, 0.4f);
		baseShader.SetUniform3f("dirLights[0].specular", 0.5f, 0.5f, 0.5f);
		// point light 1
		baseShader.SetUniform3f("pointLights[0].position", pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		baseShader.SetUniform3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		baseShader.SetUniform3f("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		baseShader.SetUniform3f("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		baseShader.SetUniform1f("pointLights[0].constant", 1.0f);
		baseShader.SetUniform1f("pointLights[0].linear", 0.09f);
		baseShader.SetUniform1f("pointLights[0].quadratic", 0.032f);
		// point light 2
		baseShader.SetUniform3f("pointLights[1].position", pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		baseShader.SetUniform3f("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		baseShader.SetUniform3f("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		baseShader.SetUniform3f("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		baseShader.SetUniform1f("pointLights[1].constant", 1.0f);
		baseShader.SetUniform1f("pointLights[1].linear", 0.09f);
		baseShader.SetUniform1f("pointLights[1].quadratic", 0.032f);
		// point light 3
		baseShader.SetUniform3f("pointLights[2].position", pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		baseShader.SetUniform3f("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		baseShader.SetUniform3f("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		baseShader.SetUniform3f("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		baseShader.SetUniform1f("pointLights[2].constant", 1.0f);
		baseShader.SetUniform1f("pointLights[2].linear", 0.09f);
		baseShader.SetUniform1f("pointLights[2].quadratic", 0.032f);
		// point light 4
		baseShader.SetUniform3f("pointLights[3].position", pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		baseShader.SetUniform3f("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		baseShader.SetUniform3f("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		baseShader.SetUniform3f("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		baseShader.SetUniform1f("pointLights[3].constant", 1.0f);
		baseShader.SetUniform1f("pointLights[3].linear", 0.09f);
		baseShader.SetUniform1f("pointLights[3].quadratic", 0.032f);
		// spotLight
		baseShader.SetUniform3f("spotLights[0].position", viewPos.x, viewPos.y, viewPos.z);
		baseShader.SetUniform3f("spotLights[0].direction", lookDir.x, lookDir.y, lookDir.z);
		baseShader.SetUniform3f("spotLights[0].ambient", 0.0f, 0.0f, 0.0f);
		baseShader.SetUniform3f("spotLights[0].diffuse", 1.0f, 1.0f, 1.0f);
		baseShader.SetUniform3f("spotLights[0].specular", 1.0f, 1.0f, 1.0f);
		baseShader.SetUniform1f("spotLights[0].constant", 1.0f);
		baseShader.SetUniform1f("spotLights[0].linear", 0.09f);
		baseShader.SetUniform1f("spotLights[0].quadratic", 0.032f);
		baseShader.SetUniform1f("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
		baseShader.SetUniform1f("spotLights[0].cutOffOuter", glm::cos(glm::radians(15.0f)));
		
		model = glm::mat4(1.0f);
		for (unsigned int i = 0; i < sizeof(cubePositions)/sizeof(cubePositions[0]); i++)
		{
			glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::translate(trans, cubePositions[i]);
			float angle = 20.0f * i;
			trans = glm::rotate(trans, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			normals = glm::transpose(glm::inverse(trans));
			baseShader.SetUniform4fv("model", glm::value_ptr(trans));
			baseShader.SetUniform3fv("normals", glm::value_ptr(normals));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	glfwTerminate();
	return 0;
}