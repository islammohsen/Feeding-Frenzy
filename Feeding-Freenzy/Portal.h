#pragma once
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Renderer.h"
#include <gL\glew.h>
#include <gl\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Portal
{
	VertexArray *m_vao;
	VertexBuffer *m_vbo;
	IndexBuffer *m_ibo;
	Texture *m_texture;
public:
	Portal(void *data, unsigned int size, unsigned int *indexData, unsigned int count, string texture);
	~Portal();
	void Draw(Renderer *renderer, Shader *shader, glm::mat4 view, glm::mat4 projection);
};

