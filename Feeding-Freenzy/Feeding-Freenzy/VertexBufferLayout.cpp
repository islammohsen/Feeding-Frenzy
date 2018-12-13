#include "VertexBufferLayout.h"



VertexBufferLayout::VertexBufferLayout(): m_Stride(0)
{
}

template<typename T>
void VertexBufferLayout::push(unsigned int count)
{
	static_assert(false);
}

template<>
void VertexBufferLayout::push<float>(unsigned int count)
{
	VertexBufferElement element;
	element.type = GL_FLOAT;
	element.typeSize = sizeof(GLfloat);
	element.count = count;
	element.normalized = GL_FALSE;
	m_Elements.push_back(element);
	m_Stride += sizeof(GLfloat) * count;
}

template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
	VertexBufferElement element;
	element.type = GL_UNSIGNED_INT;
	element.typeSize = sizeof(GLuint);
	element.count = count;
	element.normalized = GL_FALSE;
	m_Elements.push_back(element);
	m_Stride += sizeof(GLuint) * count;
}

template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
	VertexBufferElement element;
	element.type = GL_UNSIGNED_BYTE;
	element.typeSize = sizeof(GLbyte);
	element.count = count;
	element.normalized = GL_TRUE;
	m_Elements.push_back(element);
	m_Stride += sizeof(GLbyte) * count;
}


unsigned int VertexBufferLayout::GetStride() const
{
	return m_Stride;
}

const vector<VertexBufferElement>& VertexBufferLayout::GetElements() const
{
	return m_Elements;
}

VertexBufferLayout::~VertexBufferLayout()
{
}
