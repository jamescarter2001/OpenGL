#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const {
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	vb.Bind();

	std::vector<VertexBufferElement> elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const VertexBufferElement& element = elements[i];
		glEnableVertexAttribArray(i);
		// layout location assign, x floats make up a vertex position, data type of vertex attribute, don't normalise, total vertex size in bytes, number of bytes before desired attribute (typecast sizeof to void*).
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (void*) offset);
		offset += VertexBufferLayout::GetSizeOfType(element.type) * element.count;
	}
}