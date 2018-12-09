#include "Level.h"

Level::Level(int levelNumber)
{
	float backgroundPoints[] = {
		0.0f,    0.0f,   0.0f, 0.0f, 0.0f,
		0.0f,    720.0f, 0.0f, 0.0f, 1.0f,
		1024.0f, 720.0f, 0.0f, 1.0f, 1.0f,
		1024.0f, 0.0f,   0.0f, 1.0f, 0.0f
	};
	unsigned int index[] = { 0, 1, 2, 2, 3, 0 };
	background = new Background(backgroundPoints, sizeof(backgroundPoints), index, 6, "Resources/Textures/Background/BackGround-2.png" );

	float boarderPoints[] = {
		100.0f, 100.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.1f,
		100.0f, 600.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.1f,
		900.0f, 600.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.1f,
		900.0f, 100.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.1f,
	};

	unsigned int index2[] = { 0, 1, 1, 2, 2, 3, 3, 0 };
	boarder = new Boarder(boarderPoints, sizeof(boarderPoints), index2, 8);
}

Level::~Level()
{
}

void Level::DrawBackground(Renderer * renderer, Shader * m_shader, glm::mat4 view, glm::mat4 projection)
{
	background->Draw(renderer, m_shader, view, projection);
}

void Level::DrawBoarder(Renderer * renderer, Shader * m_shader, glm::mat4 view, glm::mat4 projection)
{
	boarder->Draw(renderer, m_shader, view, projection);
}

Boarder::Boarder(void * data, unsigned int size, unsigned int * indexData, unsigned int count)
{
	m_vao = new VertexArray();
	m_vbo = new VertexBuffer(data, size);
	VertexBufferLayout Layout;
	Layout.push<float>(3);
	Layout.push<float>(4);
	m_vao->AddBuffer(*m_vbo, Layout);
	m_ibo = new IndexBuffer(indexData, count);
}

void Boarder::Draw(Renderer *renderer, Shader* m_shader, glm::mat4 view, glm::mat4 projection)
{
	m_shader->Bind();
	m_shader->SetUniformMat4f("u_MVP", projection * view * glm::mat4(1));
	renderer->Draw(m_vao, m_ibo, m_shader, GL_LINES);
}

Background::Background(void * data, unsigned int size, unsigned int * indexData, unsigned int count, string texture)
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

void Background::Draw(Renderer * renderer, Shader * m_shader, glm::mat4 view, glm::mat4 projection)
{
	m_shader->Bind();
	m_shader->SetUniformMat4f("u_MVP", projection * view * glm::mat4(1));
	m_shader->setUniform1i("myTextureSampler", 1);
	m_texture->Bind(1);
	renderer->Draw(m_vao, m_ibo, m_shader, GL_TRIANGLES);
}
