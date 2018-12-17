#include "Fish.h"	 

Fish::Fish()
{

}

Fish::Fish(float xPos, float yPos, float zPos, float m_Xscale, float m_Yscale, float m_Zscale, float m_speed, int type, string object, string texture)
{
	this->type = type;
	this->m_speed = m_speed;
	model = ModelLoader::LoadModel(object);
	GetCollisionPoints();
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
	glm::mat4 modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix * model.m_rotation;
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

void Fish::ResetRotation()
{
	m_rotationMatrix = glm::mat4(1);
}

int Fish::GetType()
{
	return type;
}

glm::vec2 Fish::GetPosition()
{
	glm::vec4 ret = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
	ret = modelMatrix * ret;
	return glm::vec2(ret.x, ret.y);
}

glm::vec2 Fish::GetMouth()
{
	glm::vec4 ret = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
	ret = modelMatrix * ret;
	return glm::vec2(ret.x, ret.y);
}

vector<glm::vec2> Fish::GetCollisionPolygon()
{
	glm::mat4 modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
	vector<glm::vec2> ret;
	for (glm::vec2 currentPoint : collisionPolygon) {
		glm::vec4 temp = glm::vec4(currentPoint.x, currentPoint.y, 0.0f, 1.0f);
		temp = modelMatrix * temp;
		ret.push_back(glm::vec2(temp.x, temp.y));
	}
	return ret;
}

void Fish::GetCollisionPoints()
{
	float xMin = 1e18, xMax = -1e18, yMin = 1e18, yMax = -1e18;
	for (int i = 0; i < model.m_data.size(); i += 5)
	{
		xMin = min(xMin, model.m_data[i]);
		xMax = max(xMax, model.m_data[i]);
		yMin = min(yMin, model.m_data[i + 1]);
		yMax = max(yMax, model.m_data[i + 1]);
	}
	collisionPolygon = { glm::vec2(xMin, yMax), glm::vec2(xMax, yMax), glm::vec2(xMax, yMin), glm::vec2(xMin, yMin) };
}

Fish::~Fish()
{
	delete m_vao;
	delete m_vbo;
	delete m_ibo;
	delete m_texture;
}


