#pragma once

#include <GL/glew.h>

template<unsigned int TYPE, typename T> class GraphicsBuffer {
private:
	unsigned int m_Type;
protected:
	unsigned int m_RendererID;

	GraphicsBuffer(const T data, const unsigned int size) : m_Type(TYPE) {
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(m_Type, m_RendererID);
		glBufferData(m_Type, size, data, GL_STATIC_DRAW);
	}

	~GraphicsBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

public:

	void Bind() const {
		glBindBuffer(m_Type, m_RendererID);
	}

	void Unbind() const {
		glBindBuffer(m_Type, 0);
	}
};