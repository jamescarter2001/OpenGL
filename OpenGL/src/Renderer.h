#pragma once
#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"



void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void* userParam);

class Renderer {
public:
	Renderer();
	~Renderer();

	void Clear() const;
	void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
};