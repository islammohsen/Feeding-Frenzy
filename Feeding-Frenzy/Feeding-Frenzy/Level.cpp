#include "Level.h"

Level::Level(int levelNumber)
{
	vector<string> texture;
	for(int i = 0; i < 5; i++)
		texture.push_back("Resources/Textures/Background/background2.png");
	background = new Background(0.0f, 0.0f, -1.0f, 1024.0f, 720.0f, 3.0f, texture);
	fishType1Counter = 3;
	fishType2Counter = 3;
	fishType3Counter = 3;
}

Level::~Level()
{
}

void Level::DrawBackground(Renderer * renderer, Shader * m_shader, glm::mat4 view, glm::mat4 projection)
{
	background->Draw(renderer, m_shader, view, projection);
}

int Level::getFishType1Counter()
{
	return fishType1Counter;
}

int Level::getFishType2Counter()
{
	return fishType2Counter;
}

int Level::getFishType3Counter()
{
	return fishType3Counter;
}

Background::Background(float x,float y,float z,float x_scale, float y_scale, float z_scale, vector<string> texture)
{
	 BackgroundPoints = {
		 ////back
		 -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f
	};
	Backgroundindex = { 0,1,2,2,3,0 };
	for (auto &s : texture)
	{
		m_texture.push_back(new Texture(s));
	}
	this->x_scale = x_scale;
	this->y_scale = y_scale;
	this->z_scale = z_scale;
	m_vao = new VertexArray();
	m_vbo = new VertexBuffer(BackgroundPoints.data(), (BackgroundPoints.size() * sizeof(float)));
	m_ibo = new IndexBuffer(Backgroundindex.data(), Backgroundindex.size());
	VertexBufferLayout Layout;
	Layout.push<float>(3);
	Layout.push<float>(2);
	m_vao->AddBuffer(*m_vbo, Layout);
	this->move(x, y, z);
	this->scale(x_scale, y_scale, z_scale);
}

//back right left top bottom
void Background::Draw(Renderer * renderer, Shader * m_shader, glm::mat4 view, glm::mat4 projection)
{
	m_shader->Bind();

	
	//back
	glm::mat4 MVP1 = m_scaleMatrix * m_rotationMatrix * m_translationMatrix;
	m_shader->SetUniformMat4f("u_MVP", projection * view * MVP1);
	m_shader->setUniform1i("myTextureSampler", 1);
	m_texture[0]->Bind(1);
	renderer->Draw(m_vao, m_ibo, m_shader, GL_TRIANGLES);

	//right
	glm::mat4 MVP2 = glm::translate(1024.0f, 0.0f, 720.0f) *  m_translationMatrix * glm::rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * m_rotationMatrix *  m_scaleMatrix * glm::scale((720.0f / 1024.0f), 1.0f, 1.0f);
	m_shader->SetUniformMat4f("u_MVP", projection * view * MVP2);
	m_shader->setUniform1i("myTextureSampler", 1);
	m_texture[1]->Bind(2);
	renderer->Draw(m_vao, m_ibo, m_shader, GL_TRIANGLES);
	
	//left
	glm::mat4 MVP3 = glm::translate(-1024.0f, 0.0f, 720.0f) *  m_translationMatrix * glm::rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * m_rotationMatrix *  m_scaleMatrix * glm::scale((720.0f / 1024.0f), 1.0f, 1.0f);
	m_shader->SetUniformMat4f("u_MVP", projection * view * MVP3);
	m_shader->setUniform1i("myTextureSampler", 1);
	m_texture[2]->Bind(1);
	renderer->Draw(m_vao, m_ibo, m_shader, GL_TRIANGLES);

	//top
	glm::mat4 MVP4 = glm::translate(0.0f, 720.0f, 720.0f) *  m_translationMatrix * glm::rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f)) * m_rotationMatrix * m_scaleMatrix;
	m_shader->SetUniformMat4f("u_MVP", projection * view * MVP4);
	m_shader->setUniform1i("myTextureSampler", 1);
	m_texture[3]->Bind(1);
	renderer->Draw(m_vao, m_ibo, m_shader, GL_TRIANGLES);

	//down
	glm::mat4 MVP5 = glm::translate(0.0f, -720.0f, 720.0f) *  m_translationMatrix * glm::rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f)) * m_rotationMatrix * m_scaleMatrix;
	m_shader->SetUniformMat4f("u_MVP", projection * view * MVP5);
	m_shader->setUniform1i("myTextureSampler", 1);
	m_texture[4]->Bind(1);
	renderer->Draw(m_vao, m_ibo, m_shader, GL_TRIANGLES);
}

void Background::move(float valx, float valy, float valz)
{
	m_translationMatrix = glm::translate(m_translationMatrix, glm::vec3(valx, valy, valz));
}


void Background::rotate(float angle, float x, float y, float z)
{
	m_rotationMatrix = glm::rotate(m_rotationMatrix, angle, glm::vec3(x, y, z));
}


void Background::scale(float valx, float valy, float valz)
{
	m_scaleMatrix = glm::scale(m_scaleMatrix, glm::vec3(valx, valy, valz));
}