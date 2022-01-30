#pragma once

#include "GraphicsBuffer.h"

class VertexBuffer : public GraphicsBuffer<GL_ARRAY_BUFFER, const void*> {
public:
	VertexBuffer(const void* data, const unsigned int size);
	~VertexBuffer();
};