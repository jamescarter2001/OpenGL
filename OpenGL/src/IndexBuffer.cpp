#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int size) : m_Count(size / sizeof(unsigned int)), GraphicsBuffer(data, size) {}

IndexBuffer::~IndexBuffer() {}