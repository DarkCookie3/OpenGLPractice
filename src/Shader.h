#pragma once

#include "GLAD/glad.h"
#include <string>
#include "glm/gtc/type_ptr.hpp"
#include <unordered_map>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepathVertex, const std::string& filepathGeometry);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
	void SetUniform4fv(const std::string& name, const GLfloat *value);
private:
	ShaderProgramSource ParseShader(const std::string& filepathVertex, const std::string& filepathFragment, const std::string& filepathGeometry = "");
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int GetUniformLocation(const std::string& name);
};