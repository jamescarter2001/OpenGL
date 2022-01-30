#pragma once
#include <GL/glew.h>

#include "GraphicsBuffer.h"

class IndexBuffer : public GraphicsBuffer<GL_ELEMENT_ARRAY_BUFFER, const unsigned int*> {
private:
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int size);
	~IndexBuffer();

	inline int GetCount() const {
		return m_Count;
	}
};