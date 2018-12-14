#include "Fish.h"	 

Fish::Fish()
{

}

Fish::Fish(float xPos, float yPos, float zPos, float m_Xscale, float m_Yscale, float m_Zscale, float m_speed, string object, string texture)
{
	this->m_speed = m_speed;
	this->m_scale = m_Xscale * m_Yscale * m_Zscale;
	model = ModelLoader::LoadModel(object);
	for (int i = 0; i < model.m_data.size(); i++)
		index.push_back(i);
	m_texture = new Texture(texture);
	m_vao = new VertexArray();
	m_vbo = new VertexBuffer(model.m_data.data(), (model.m_data.size() * sizeof(float)));
	m_ibo = new IndexBuffer(index.data(), index.size());
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);
	m_vao->AddBuffer(*m_vbo, layout);
	this->move(xPos, yPos, zPos);
	this->scale(m_Xscale, m_Yscale, m_Zscale);
}




void Fish::Draw(Renderer *renderer, Shader* m_shader, glm::mat4 view, glm::mat4 projection)
{
	m_shader->Bind();
	glm::mat4 modelMatrix = m_translationMatrix * m_rotationMatrix * model.m_rotation * m_scaleMatrix;
	m_shader->SetUniformMat4f("u_MVP", projection * view * modelMatrix);
	m_shader->setUniform1i("myTextureSampler", 0);
	m_texture->Bind(0);
	renderer->Draw(m_vao, m_ibo, m_shader, GL_TRIANGLES);
}


void Fish::move(float valx, float valy, float valz)
{
	m_translationMatrix = glm::translate(m_translationMatrix, glm::vec3(valx, valy, valz));
}


void Fish::rotate(float angle, float x, float y, float z)
{
	m_rotationMatrix *= glm::rotate(angle, glm::vec3(x, y, z));
}


void Fish::scale(float valx, float valy, float valz)
{
	m_scaleMatrix = glm::scale(m_scaleMatrix, glm::vec3(valx, valy, valz));
}


Fish::~Fish()
{
	delete m_vao;
	delete m_vbo;
	delete m_ibo;
	delete m_texture;
}


