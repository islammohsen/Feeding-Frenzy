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

class Fish  
{
	VertexArray *m_vao;
	IndexBuffer *m_ibo;
	VertexBuffer *m_vbo;
	Texture *m_texture;
	float m_scale;
	float m_speed;
	GLint m_count;
	glm::mat4 m_model;

public:

	Fish(void *data, unsigned int size, unsigned int *indexData, unsigned int count, string texture, float m_speed, float m_scale);
	void Draw(Renderer *renderer, Shader* m_shader, glm::mat4 view, glm::mat4 projection);

	~Fish();
};

