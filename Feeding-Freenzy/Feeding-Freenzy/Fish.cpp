#include "Fish.h"



Fish::Fish(void *data, unsigned int size, unsigned int *indexData, unsigned int count, string texture, float m_speed, float m_scale)
{
	m_texture = new Texture(texture);
	this->m_speed = m_speed;
	this->m_scale = m_scale;
	m_count = count;
	m_vao = new VertexArray();
	m_vbo = new VertexBuffer(data,size);
	m_ibo = new IndexBuffer(indexData, count);
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);
	m_vao->AddBuffer(*m_vbo, layout);
}

void Fish::Draw(Renderer *renderer, Shader* m_shader, glm::mat4 view, glm::mat4 projection)
{
	m_shader->Bind();
	m_shader->SetUniformMat4f("u_MVP", projection * view * m_model);
	m_shader->setUniform1i("myTextureSampler", 0);
	m_texture->Bind(0);
	renderer->Draw(m_vao, m_ibo, m_shader, GL_TRIANGLES);
}

Fish::~Fish()
{
}
