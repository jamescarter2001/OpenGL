#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <GL/glew.h>

#include "glm/glm.hpp"

struct ShaderProgramSource {
	std::string vertexShader;
	std::string fragmentShader;
};

enum class ShaderType {
	NONE = -1,
	VERTEX = 1,
	FRAGMENT = 2
};


class Shader {
private:
	unsigned int m_RendererID;
	std::string m_filePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	ShaderProgramSource ParseShader() const;
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const;
	unsigned int CompileShader(const std::string& source, const unsigned int type) const;
	int GetUniformLocation(const std::string& name);
public:
	Shader(std::string& filePath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, const int v1);

	void SetUniform4f(const std::string& name, const float v1, const float v2, const float v3, const float v4);

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
};