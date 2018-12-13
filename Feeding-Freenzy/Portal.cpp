#include "Portal.h"



Portal::Portal(void *data, unsigned int size, unsigned int *indexData, unsigned int count, string texture)
{
	m_vao = new VertexArray();
	m_vbo = new VertexBuffer(data, size);
	VertexBufferLayout Layout;
	Layout.push<float>(3);
	Layout.push<float>(2);
	m_vao->AddBuffer(*m_vbo, Layout);
	m_ibo = new IndexBuffer(indexData, count);
	m_texture = new Texture(texture);
}

Portal::~Portal()
{
}

void Portal::Draw(Renderer *renderer, Shader *shader, glm::mat4 view, glm::mat4 projection)
{
	m_vao->Bind();
	m_texture->Bind(0);
	shader->SetUniformMat4f("u_MVP", projection * view * glm::mat4(1));
	shader->setUniform1i("myTextureSampler", 0);
	renderer->Draw(m_vao, m_ibo, shader, GL_TRIANGLES);
}
